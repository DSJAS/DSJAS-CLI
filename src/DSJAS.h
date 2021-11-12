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
#include <stdio.h>
#include <limits.h>

#include "iniparser.h"
#include "json.h"

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

	char path[PATH_MAX];

	char *section;
	char *cmd;
	int numSubOpts;
	char **subOpts;
} global_options;

void arg_parse(global_options *opts, int argc, char **argv);
bool validate_path(char *path);

/* DSJAS config/state */
typedef enum InstallState {
	greeting = 1,
	verification = 2,
	database = 3,
	finalised = 4
} InstallState;

typedef struct dsjas_install {
	struct {
		dictionary *glb;
		dictionary *thm;
		dictionary *mod;
		dictionary *ext;

		struct {
			bool installed;
			InstallState installState;

			bool usingDatabase;
			char *hostname;
			char *dbName;
			char *un;
			char *pw;

			char *name;
			char *domain;

			bool adminDisabled;
			bool adminMissing;
		} global;

		struct {
			bool udefault;
			const char *cur;
		} theme;

		struct {
			char **installed;
			char **enabled;

			int numInstalled;
			int numEnabled;
		} module;

		struct {
			char placeholder;
		} extension;
	} config;

	struct {
		FILE *versConfig;
		json_value *vers;

		int major;
		int minor;
		int patch;

		char *name;
		char *description;
	} version;
} DSJAS;

#endif // UTIL_H_
