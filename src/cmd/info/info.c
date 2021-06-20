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
#include <stdbool.h>

#include "util/util.h"

#include "info.h"
#include "sub.h"

static void info_general()
{
	out_msg("General settings:\n");
	out_msg("-----------------\n");

	out_msg("\t");
	out_put("Bank name: \"%s\"\n", gInstall.config.global.name);

	out_msg("\t");
	out_put("Bank URL: \"%s\"\n", gInstall.config.global.domain);

	out_msg("\t");
	out_put("Admin panel disabled: ");
	if (gInstall.config.global.adminDisabled) {
		out_msgc("true\n", TERMCOLOR_GREEN);
	} else {
		out_msgc("false\n", TERMCOLOR_RED);
	}

	out_msg("\t");
	out_put("Admin panel concealed: ");
	if (gInstall.config.global.adminMissing) {
		out_msgc("true\n", TERMCOLOR_GREEN);
	} else {
		out_msgc("false\n", TERMCOLOR_RED);
	}
}

static void info_theme()
{
	out_msg("Theme settings:\n");
	out_msg("---------------\n");

	out_msg("\t");
	out_put("Default theme enabled: ");
	if (gInstall.config.theme.udefault) {
		out_msgc("true\n", TERMCOLOR_GREEN);
	} else {
		out_msgc("false\n", TERMCOLOR_RED);
	}

	out_msg("\t");
	out_put("Enabled theme: \"%s\"\n", gInstall.config.theme.cur);
}

static void info_summary()
{
	out_msg("DSJAS Configuration summary\n");
	out_msg("===========================\n\n");

	info_theme();
	info_general();
}

static void info_config()
{
	const char *global = "/Config.ini";
	const char *theme = "/admin/site/UI/config.ini";
	const char *module = "/admin/site/modules/config.ini";
	const char *extens = "/admin/site/extensions/config.ini";

	out_msg("Configuration information\n");
	out_msg("=========================\n");

	out_msg("\tGlobal config path: ");
	out_put("%s%s\n", gOpts.path, global);

	out_msg("\tTheme config path: ");
	out_put("%s%s\n", gOpts.path, theme);

	out_msg("\tModule config path: ");
	out_put("%s%s\n", gOpts.path, module);

	out_msg("\tExtension config path: ");
	out_put("%s%s\n", gOpts.path, extens);
}

void info_init()
{
	char *cmd = gOpts.cmd;
	if (strcmp(cmd, "summary") == 0) {
		info_summary();
	} else if (strcmp(cmd, "config") == 0) {
		info_config();
	} else {
		err("Unknown subcommand");
		exit(-1);
	}

	return;
}
