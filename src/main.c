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
#include "util.h"
#include "ver.h"

global_options gOpts;

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

	puts("\nGlobal options:");
	puts("\t-V: Verbose output");
	puts("\t-q: Quiet output");
	puts("\t-p: Set DSJAS path");
	puts("\t-u: Print usage");
	puts("\t-h: This message");

	puts("\nCommand sections");
	puts("\tcreate: Create themes, modules and extensions from boilerplates");
	puts("\tinfo: Get info about a DSJAS install");

	exit(-1);
}

void version()
{
	puts("dsjas: DSJAS-CLI Tool");
	printf("Version %i.%i.%i, built at %s %s\n", major_ver, minor_ver,
		   patch_ver, build_date, build_time);
	exit(-1);
}

int main(int argc, char **argv)
{
	/* Parse argument array */
	arg_parse(&gOpts, argc, argv);

	/* Verify installation */
	if (!path_isInstall(gOpts.path)) {
		err("Invalid DSJAS install");
		return -1;
	}

	/* Pass control to subcommand */
	if (strcmp(gOpts.section, "create") == 0) {
	} else if (strcmp(gOpts.section, "info") == 0) {
	} else {
		err("Invalid subcommand");
		help();
	}

	return 0;
}
