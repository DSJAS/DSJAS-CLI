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

#include <stdbool.h>

#ifndef __EXT_H__
#define __EXT_H__

/* Theme */
typedef struct {
	const char *path;
	const char *name;
} Theme;

void init_theme(Theme *theme);
void free_theme(Theme *theme);
void create_theme(const char *name);

/* Module */
typedef struct {
	const char *path;
	const char *name;
	const char *description;
	const char *info_link;

	int v_maj;
	int v_min;
	int v_pat;

	char **routes;
	char **route_events;
	bool *route_props[3];

	const char **filter;
} Module;

void init_module(Module *module);
void free_module(Module *module);
void create_module(const char *name, const char *description,
				   const char *info_link, const int *ver, const char **hooks,
				   const char **events, const bool **props);

#endif
