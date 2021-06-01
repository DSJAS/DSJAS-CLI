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
	out_put("Bank name: \"");
	out_put(gInstall.config.global.name);
	out_put("\"\n");

	out_msg("\t");
	out_put("Bank URL: \"");
	out_put(gInstall.config.global.domain);
	out_put("\"\n");

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
	out_put("Enabled theme: ");
	out_put(gInstall.config.theme.cur);
	out_put("\n");
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
	const char *module = "/admin/site/module/config.ini";
	const char *extens = "/admin/site/extensions/config.ini";

	char globalC[strlen(global) + strlen(gOpts.path) + 1];
	char themeC[strlen(theme) + strlen(gOpts.path) + 1];
	char moduleC[strlen(module) + strlen(gOpts.path) + 1];
	char extensC[strlen(extens) + strlen(gOpts.path) + 1];

	sprintf(globalC, "%s%s", gOpts.path, global);
	sprintf(themeC, "%s%s", gOpts.path, theme);
	sprintf(moduleC, "%s%s", gOpts.path, module);
	sprintf(extensC, "%s%s", gOpts.path, extens);

	out_msg("Configuration information\n");
	out_msg("=========================\n");

	out_msg("\t");
	out_put("Global config path: ");
	out_put(globalC);
	out_put("\n");

	out_msg("\t");
	out_put("Theme config path: ");
	out_put(themeC);
	out_put("\n");

	out_msg("\t");
	out_put("Module config path: ");
	out_put(moduleC);
	out_put("\n");

	out_msg("\t");
	out_put("Extension config path: ");
	out_put(extensC);
	out_put("\n");
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
