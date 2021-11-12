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
#include <getopt.h>

#include "conf/conf.h"
#include "util/util.h"
#include "cmd/common.h"
#include "ext/ext.h"

#include "sub.h"

static const char *opts = "ht:m:";

static bool filterTheme = false;
static bool filterModule = false;

static char *themeFilter;
static char *moduleFilter;

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

static void info_filter_theme()
{
	Theme thm;
	if (!init_theme(&thm, themeFilter)) {
		err("Unknown theme \"%s\"", themeFilter);

		free_theme(&thm);
		exit(-1);
	}

	out_msg("Theme information\n");
	out_msg("-----------------\n");

	out_msg("\t");
	out_put("Theme name: %s\n", thm.name);

	out_msg("\t");
	out_put("Theme path: %s\n", thm.path);

	out_msg("\t");
	out_put("Theme enabled: ");
	if (thm.enabled) {
		out_msgc("true", TERMCOLOR_GREEN);
	} else {
		out_msgc("false", TERMCOLOR_RED);
	}
	putchar('\n');

	free_theme(&thm);
}

static void info_theme()
{
	if (filterTheme) {
		info_filter_theme();
		return;
	}

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

static void info_filter_module()
{
	Module mod;
	if (!init_module(&mod, moduleFilter)) {
		err("Error parsing module");

		exit(-1);
	}

	free_module(&mod);
}

static void info_module()
{
	if (filterModule) {
		info_filter_module();
		return;
	}

	out_msg("Module settings:\n");
	out_msg("----------------\n");

	out_msg("\t");
	out_put("Enabled modules: ");

	out_msg("\n");

	for (int i = 0; i < gInstall.config.module.numEnabled; i++) {
		out_msg("\t\t");
		if (gOpts.quiet) {
			out_put("%s", gInstall.config.module.enabled[i]);
			if (i != gInstall.config.module.numEnabled - 1) {
				out_put(", ");
			} else {
				out_put("\n");
			}
		} else {
			out_put("%s\n", gInstall.config.module.enabled[i]);
		}
	}

	out_msg("\t");
	out_put("All modules: ");
	out_msg("\n");

	for (int i = 0; i < gInstall.config.module.numInstalled; i++) {
		out_msg("\t\t");
		if (gOpts.quiet) {
			out_put("%s", gInstall.config.module.installed[i]);
			if (i != gInstall.config.module.numInstalled - 1) {
				out_put(", ");
			} else {
				out_put("\n");
			}
		} else {
			out_put("%s\n", gInstall.config.module.installed[i]);
		}
	}
}

static void info_extension()
{
	out_msg("Extension settings:\n");
	out_msg("-------------------\n");

	if (!gOpts.quiet) {
		out_msgc("\tComing soon\n", TERMCOLOR_YELLOW);
	}
}

static void info_summary()
{
	out_msg("DSJAS Configuration summary\n");
	out_msg("===========================\n\n");

	info_general();
	info_theme();
	info_module();
	info_extension();
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

void info_help()
{
	execlp("/usr/bin/man", "/usr/bin/man", "dsjas-info", NULL);
}

void info_init()
{
	int opt;
	optind = 1;
	while ((opt = getopt(gOpts.numSubOpts, gOpts.subOpts, opts)) != -1) {
		switch (opt) {
		case 'h':
			info_help();
			exit(-1);
		case 't':
			msg("Filtering for theme \"%s\"", optarg);
			filterTheme = true;
			themeFilter = optarg;
			break;
		case 'm':
			msg("Filtering for module \"%s\"", optarg);
			filterModule = true;
			moduleFilter = optarg;
			break;
		default:
			exit(-1);
		}
	}

	char *cmd = gOpts.cmd;
	if (strcmp(cmd, "summary") == 0) {
		info_summary();
	} else if (strcmp(cmd, "config") == 0) {
		info_config();
	} else if (strcmp(cmd, "site") == 0) {
		info_general();
	} else if (strcmp(cmd, "theme") == 0) {
		info_theme();
	} else if (strcmp(cmd, "module") == 0) {
		info_module();
	} else if (strcmp(cmd, "extension") == 0) {
		info_extension();
	} else {
		error_command_unknown();
	}

	return;
}
