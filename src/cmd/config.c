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

#include <unistd.h>
#include <sys/wait.h>

#include <util/util.h>
#include <cmd/common.h>

#include "sub.h"

extern char confPath[PATH_MAX];
extern char versionPath[PATH_MAX];
extern char themeConfPath[PATH_MAX];
extern char moduleConfPath[PATH_MAX];

static void edit(const char *editor, const char *path)
{
	int pid = fork();
	switch (pid) {
	case 0:
		execlp(editor, editor, confPath, NULL);
		break;
	case -1:
		err("Fork failed");
		exit(-1);
		break;
	default:
		waitpid(pid, NULL, 0);
		break;
	}
}

static void edit_all(const char *editor)
{
	int pid = fork();
	switch (pid) {
	case 0:
		execlp(editor, editor, confPath, versionPath, themeConfPath,
			   moduleConfPath, NULL);
		break;
	case -1:
		err("Fork failed");
		exit(-1);
		break;
	default:
		waitpid(pid, NULL, 0);
		break;
	}
}

void config_init()
{
	const char *editor = getenv("EDITOR");

	char *cmd = gOpts.cmd;
	if (strcmp(cmd, "main") == 0) {
		edit(editor, confPath);
	} else if (strcmp(cmd, "all") == 0) {
		edit_all(editor);
	} else if (strcmp(cmd, "version") == 0) {
		edit(editor, versionPath);
	} else if (strcmp(cmd, "theme") == 0) {
		edit(editor, themeConfPath);
	} else if (strcmp(cmd, "module") == 0) {
		edit(editor, moduleConfPath);
	} else if (strcmp(cmd, "extension") == 0) {
		wrn("Coming soon");
		return;
	} else {
		error_command_unknown();
	}
}
