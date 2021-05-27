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

#ifndef __DSJAS_H__
#define __DSJAS_H__

/* Main routines */
void usage();
void help();
void version();

/* Argument parsing */
typedef struct global_options {
	int gflags_end;

	bool verbose;
	bool quiet;

	char path[256];

	char *section;
	char *cmd;
	int numSubOpts;
	char **subOpts;
} global_options;

void arg_parse(global_options *opts, int argc, char **argv);
bool path_isInstall(char *path);

#endif // UTIL_H_
