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
	asprintf(&module->path, "%s/%s%s", gOpts.path, modulePath, name);

	if (!dir_exists(module->path)) {
		err("Unknown module \"%s\"", name);

		return false;
	}

	char *config = path_addFile(module->path, "config.json");
	FILE *f = fopen(config, "r");
	long len = file_getSize(config);

	if (!f) {
		err("Invalid module: module configuration missing");

		free(config);
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
	json_value *filt_k = json_findKey("fileFilter", *module->root);

	module->name = json_getString(*name_k);
	module->description = json_getString(*desc_k);

	if (info_k)
		module->info_link = json_getString(*info_k);
	else
		module->info_link = "";

	if (sscanf(json_getString(*vers_k), "%d.%d.%d", &module->v_maj,
			   &module->v_min, &module->v_pat) != 3) {
		err("Invalid module: invalid module version specifier");

		free(config);
		return false;
	}

	module->hooks = malloc(sizeof(ModuleHook) * hook_k->u.object.length);
	for (int i = 0; i < hook_k->u.object.length; i++) {
		json_value *hook = hook_k->u.object.values[i].value;
		json_value *even_k = json_findKey("triggerEvent", *hook);

		json_value *css_k = json_findKey("loadCSS", *hook);
		json_value *js_k = json_findKey("loadJS", *hook);
		json_value *html_k = json_findKey("loadHTML", *hook);

		module->hooks[i].name = hook_k->u.object.values[i].name;
		module->hooks[i].event = json_getString(*even_k);

		if (css_k && json_getBool(*css_k)) {
			module->hooks[i].flags |= MODHOOK_CSS;
		}

		if (js_k && json_getBool(*js_k)) {
			module->hooks[i].flags |= MODHOOK_JS;
		}

		if (html_k && json_getBool(*html_k)) {
			module->hooks[i].flags |= MODHOOK_HTML;
		}
	}

	if (filt_k) {
		module->filter = malloc(sizeof(char **) * filt_k->u.array.length);
		for (int i = 0; i < filt_k->u.array.length; i++) {
			module->filter[i] = json_getString(*filt_k->u.array.values[i]);
		}
	} else {
		module->filter = NULL;
	}

	free(config);
	free(json);
	fclose(f);

	return true;
}

void free_module(Module *module)
{
	free(module->path);
	free(module->hooks);

	if (module->filter)
		free(module->filter);

	json_value_free(module->root);
}

void create_module(const char *name, const char *description,
				   const char *info_link, const int *ver, const char **hooks,
				   const char **events, const bool **props)
{
}
