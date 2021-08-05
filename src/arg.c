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

#include <stdio.h>
#include <dirent.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

#include "DSJAS.h"
#include "util/util.h"

static const char *globOpts = "+huvVqp:";

static const char *installFiles[] = {"Index.php",
									 "Config.ini",
									 "admin/site/UI/config.ini",
									 "admin/site/modules/config.ini",
									 "admin/site/extensions/config.ini",
									 "Version.json",
									 ".htaccess",
									 NULL};
static const int installFileModes[] = {R_OK, W_OK, W_OK, W_OK,
									   W_OK, W_OK, R_OK};

void arg_parse(global_options *opts, int argc, char **argv)
{
	bool pathOverride = false;

	int opt;
	while ((opt = getopt(argc, argv, globOpts)) != -1) {
		switch (opt) {
		case 'h':
			help();
			break;
		case 'u':
			usage();
			break;
		case 'v':
			version();
			break;
		case 'V':
			opts->verbose = true;
			break;
		case 'q':
			opts->quiet = true;
			break;
		case 'p':
			strncpy(opts->path, optarg, PATH_MAX - 1);
			pathOverride = true;
			break;
		case '?':
			exit(-1);
		default:
			goto end;
		}
	}

end:
	if (optind < argc) {
		if (argv[optind][0] == '-') {
			usage();
		}
	}

	if (!pathOverride) {
		getcwd(opts->path, PATH_MAX);
	}

	opts->gflags_end = optind;

	if (optind + 2 > argc) {
		err("Expected [section] [command]");
		usage();
	}

	opts->section = argv[optind];
	opts->cmd = argv[optind + 1];
	opts->numSubOpts = argc - optind - 1;
	opts->subOpts = &argv[optind + 1];
}

bool path_isInstall(char *path)
{
	if (!dir_exists(path)) {
		return false;
	}

	int i = 0;
	while (installFiles[i] != NULL) {
		int mode = installFileModes[i];
		char *file = path_addFile(path, installFiles[i]);

		if ((!access(file, mode)) == 0) {
			free(file);
			return false;
		}

		free(file);
		i++;
	}

	return true;
}
