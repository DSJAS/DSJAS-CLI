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

#include <dirent.h>
#include <stdbool.h>

#include "json.h"

#ifndef __EXT_H__
#define __EXT_H__

/* Theme */
typedef struct {
	char *path;
	char *name;

	bool enabled;
} Theme;

bool init_theme(Theme *theme, char *name);
void free_theme(Theme *theme);
void create_theme(const char *name);

/* Module */
#define MODHOOK_CSS  0x1
#define MODHOOK_JS   0x2
#define MODHOOK_HTML 0x4

typedef struct {
	char *name;
	char *event;
	char flags;
} ModuleHook;

typedef struct {
	json_value *root;

	char *path;
	char *name;
	char *description;
	char *info_link;

	int v_maj;
	int v_min;
	int v_pat;

	ModuleHook *hooks;

	char **filter;
} Module;

bool init_module(Module *module, char *name);
void free_module(Module *module);
void create_module(const char *name, const char *description,
				   const char *info_link, const int *ver, const char **hooks,
				   const char **events, const bool **props);

#endif
