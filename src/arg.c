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
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "DSJAS.h"

static const char *globOpts = "huvVqp:";

void arg_parse(global_options *opts, int argc, char **argv)
{
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
			strncpy(opts->path, optarg, 255);
			break;
		default:
			exit(-1);
		}
	}

	opts->gflags_end = optind;
}
