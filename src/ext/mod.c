/*
 * This file is part of DSJAS-CLI
 *
 * Copyright (C) 2021 - Ethan Marshall
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <libgen.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdbool.h>

#include "DSJAS.h"
#include "util/util.h"
#include "json.h"
#include "conf/conf.h"
#include "ext.h"

extern DSJAS gInstall;
extern global_options gOpts;

static const char *modulePath = "admin/site/modules/";

bool init_module(Module *module, char *name)
{
	char *fullPath = path_addFile(gOpts.path, modulePath);
	module->path = path_addFile(fullPath, name);

	if (!dir_exists(module->path)) {
		return false;
	}

	char *config = path_addFile(module->path, "config.json");
	FILE *f = fopen(config, "r");
	long len = file_getSize(config);

	if (!f) {
		err("Invalid module: module configuration missing");

		free(config);
		free(fullPath);
		return false;
	}

	char *json = malloc(sizeof(char) * len);
	fread(json, sizeof(char), len, f);

	module->root = json_parse(json, len);

	json_value *name_k = json_findKey("name", *module->root);
	json_value *desc_k = json_findKey("description", *module->root);
	json_value *vers_k = json_findKey("version", *module->root);
	json_value *info_k = json_findKey("information-link", *module->root);
	json_value *hook_k = json_findKey("hooks", *module->root);

	module->name = json_getString(*name_k);
	module->description = json_getString(*desc_k);

	if (info_k)
		module->info_link = json_getString(*info_k);
	else
		module->info_link = "";

	/* TODO: Implement hooks, routes and filter parsing */

	free(fullPath);
	free(config);
	free(json);
	fclose(f);

	return true;
}

void free_module(Module *module)
{
	free(module->path);
	json_value_free(module->root);
}

void create_module(const char *name, const char *description,
				   const char *info_link, const int *ver, const char **hooks,
				   const char **events, const bool **props)
{
}
