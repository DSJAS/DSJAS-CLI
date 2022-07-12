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
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>

#include "DSJAS.h"
#include "ver.h"
#include "util/util.h"
#include "conf/conf.h"
#include "cmd/sub.h"

global_options gOpts;
DSJAS gInstall;

void usage()
{
	puts("dsjas: DSJAS-CLI Tool");
	puts("Usage: [-huvVqp] [section] [command] [args]");
	exit(-1);
}

void help()
{
	puts("dsjas: DSJAS-CLI Tool");
	puts("Usage: [-huvVqp] [section] [command] [args]");

	puts("\nGlobal options:\n"
	     "\t-V: Verbose output\n"
	     "\t-q: Quiet output\n"
	     "\t-p: Set DSJAS path\n"
	     "\t-u: Print usage\n"
	     "\t-h: This message");

	puts("\nCommand sections");
	puts("\tcreate: Create themes, modules and extensions from "
	     "boilerplates\n"
	     "\tinfo: Get info about a DSJAS install");

	exit(-1);
}

void version()
{
	puts("dsjas: DSJAS-CLI Tool");
	printf("Version %i.%i.%i, built at %s %s\n", major_ver, minor_ver,
	       patch_ver, build_date, build_time);
	exit(-1);
}

static void cleanup()
{
	/* Write and free configs */
	destroy_configs(&gInstall);
}

int main(int argc, char **argv)
{
	/* Handle redirected output */
	if (!isatty(STDOUT_FILENO) || !isatty(STDERR_FILENO)) {
		gOpts.quiet = true;
	}

	/* Parse argument array */
	arg_parse(&gOpts, argc, argv);

	/* Verify installation */
	if (!validate_path(gOpts.path)) {
		err("Invalid DSJAS install");
		return -1;
	}

	/* Init configs */
	init_configs(&gInstall);
	atexit(cleanup);

	/* Pass control to subcommand */
	if (strcmp(gOpts.section, "create") == 0) {
		create_init();
	} else if (strcmp(gOpts.section, "info") == 0) {
		info_init();
	} else if (strcmp(gOpts.section, "config") == 0) {
		config_init();
	} else {
		err("Invalid subcommand");
		help();
	}

	return 0;
}
