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
#include "ext.h"

extern DSJAS gInstall;
extern global_options gOpts;

static const char *themePath = "admin/site/UI/";

bool init_theme(Theme *theme, char *name)
{
	theme->name = name;

	char *fullPath = path_addFile(gOpts.path, themePath);
	theme->path = path_addFile(fullPath, name);

	if (!dir_exists(theme->path)) {
		return false;
	}

	theme->enabled = (strcmp(gInstall.config.theme.cur, name) == 0);

	free(fullPath);
	return true;
}

void free_theme(Theme *theme)
{
	free(theme->path);
}

void create_theme(const char *name)
{
}
