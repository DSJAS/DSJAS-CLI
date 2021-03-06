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
#include <string.h>
#include <stdbool.h>

#include "iniparser.h"
#include "json.h"

#include "conf.h"
#include "util/util.h"

extern global_options gOpts;

/* Relative path constants */
static const char *relConfPath = "Config.ini";
static const char *relThemePath = "admin/site/UI/config.ini";
static const char *relModulePath = "admin/site/modules/config.ini";
static const char *relVersionPath = "Version.json";

/* Global calculated locations */
char confPath[PATH_MAX];
char versionPath[PATH_MAX];
char themeConfPath[PATH_MAX];
char moduleConfPath[PATH_MAX];

static void init_global(DSJAS *state);
static void init_theme(DSJAS *state);
static void init_module(DSJAS *state);
static void init_extension(DSJAS *state);
static void init_version(DSJAS *state);

static void destroy_global(DSJAS *state);
static void destroy_theme(DSJAS *state);
static void destroy_module(DSJAS *state);
static void destroy_extension(DSJAS *state);
static void destroy_version(DSJAS *state);

void init_configs(DSJAS *state)
{
	init_global(state);
	init_theme(state);
	init_module(state);
	init_extension(state);

	init_version(state);
}

void destroy_configs(DSJAS *state)
{
	destroy_global(state);
	destroy_theme(state);
	destroy_module(state);
	destroy_extension(state);
	destroy_version(state);

	iniparser_freedict(state->config.glb);
	iniparser_freedict(state->config.thm);
	iniparser_freedict(state->config.mod);
	iniparser_freedict(state->config.ext);
}

static void init_global(DSJAS *state)
{
	path_concat(confPath, gOpts.path, relConfPath);

	state->config.glb = iniparser_load(confPath);

	state->config.global.name = (char *)iniparser_getstring(
	    state->config.glb, "customization:bank_name", "");
	state->config.global.domain = (char *)iniparser_getstring(
	    state->config.glb, "customization:bank_domain", "");

	state->config.global.adminDisabled = iniparser_getboolean(
	    state->config.glb, "settings:disable_admin", false);
	state->config.global.adminMissing = iniparser_getboolean(
	    state->config.glb, "settings:simulate_missing_nolog_admin", false);

	state->config.global.usingDatabase = !iniparser_getboolean(
	    state->config.glb, "database:running_without_database", false);
	state->config.global.hostname = (char *)iniparser_getstring(
	    state->config.glb, "database:server_hostname", "localhost");
	state->config.global.dbName = (char *)iniparser_getstring(
	    state->config.glb, "database:database_name", "DSJAS");
	state->config.global.un = (char *)iniparser_getstring(
	    state->config.glb, "database:username", "");
	state->config.global.pw = (char *)iniparser_getstring(
	    state->config.glb, "database:password", "");

	char *installKeys[] = {"setup:installed", "setup:owner_verified",
			       "setup:database_installed",
			       "setup:install_finalized"};
	state->config.global.installed = true;

	for (int i = 0; i < 4; i++) {
		if (!iniparser_getboolean(state->config.glb, installKeys[i],
					  false)) {
			state->config.global.installed = false;
			break;
		}

		state->config.global.installState = i + 1;
	}
}

static void init_theme(DSJAS *state)
{
	path_concat(themeConfPath, gOpts.path, relThemePath);

	state->config.thm = iniparser_load(themeConfPath);

	state->config.theme.udefault =
	    iniparser_getboolean(state->config.thm, "config:use_default", true);
	if (state->config.theme.udefault) {
		state->config.theme.cur = "default";
	} else {
		state->config.theme.cur = iniparser_getstring(
		    state->config.thm, "extensions:current_ui_extension",
		    "default");
	}
}

static void init_module(DSJAS *state)
{
	path_concat(moduleConfPath, gOpts.path, relModulePath);

	state->config.mod = iniparser_load(moduleConfPath);

	state->config.module.numInstalled =
	    iniparser_getsecnkeys(state->config.mod, "active_modules");

	state->config.module.installed =
	    malloc(sizeof(char *) * state->config.module.numInstalled);

	state->config.module.enabled =
	    malloc(sizeof(char *) * state->config.module.numInstalled);

	iniparser_getseckeys(state->config.mod, "active_modules",
			     (const char **)state->config.module.installed);

	state->config.module.numEnabled = 0;
	for (int i = 0; i < state->config.module.numInstalled; i++) {
		char *modName =
		    strchr(state->config.module.installed[i], ':') + 1;
		bool enabled = iniparser_getboolean(
		    state->config.mod, state->config.module.installed[i],
		    false);

		state->config.module.installed[i] = modName;
		if (enabled) {
			state->config.module
			    .enabled[state->config.module.numEnabled++] =
			    modName;
		}
	}
}

static void init_extension(DSJAS *state)
{
	state->config.extension.placeholder = 'A';
}

static void init_version(DSJAS *state)
{
	path_concat(versionPath, gOpts.path, relVersionPath);

	FILE *f = fopen(versionPath, "r+");

	if (!f) {
		err("Failed to open version config file");
		exit(-1);
	}

	state->version.versConfig = f;
	long len = file_size(versionPath);

	char *cont = malloc(sizeof(char) * len);
	fread(cont, sizeof(char), len, f);

	state->version.vers = json_parse(cont, len);

	json_value *name = json_findKey("version-name", *state->version.vers);
	json_value *desc =
	    json_findKey("version-description", *state->version.vers);

	json_value *vers = json_findKey("version", *state->version.vers);
	json_value *major = json_findKey("major", *vers);
	json_value *minor = json_findKey("minor", *vers);
	json_value *patch = json_findKey("patch", *vers);

	state->version.name = json_getString(*name);
	state->version.description = json_getString(*desc);
	state->version.major = json_getInt(*major);
	state->version.minor = json_getInt(*minor);
	state->version.patch = json_getInt(*patch);

	free(cont);
}

static void destroy_global(DSJAS *state)
{
	char gfn[PATH_MAX];
	path_concat(gfn, gOpts.path, "Config.ini");

	FILE *gf = fopen(gfn, "r+");

	ini_serialise(state->config.glb, gf);

	fclose(gf);
}

static void destroy_theme(DSJAS *state)
{
	char tfn[PATH_MAX];
	path_concat(tfn, gOpts.path, "admin/site/UI/config.ini");

	FILE *tf = fopen(tfn, "r+");
	ini_serialise(state->config.thm, tf);

	fclose(tf);
}

static void destroy_module(DSJAS *state)
{
	char mfn[PATH_MAX];
	path_concat(mfn, gOpts.path, "admin/site/modules/config.ini");

	FILE *tf = fopen(mfn, "r+");
	ini_serialise(state->config.mod, tf);

	free(state->config.module.installed);
	free(state->config.module.enabled);

	fclose(tf);
}

static void destroy_extension(DSJAS *state)
{
	return;
}

static void destroy_version(DSJAS *state)
{
	json_value_free(state->version.vers);
	fclose(state->version.versConfig);
}
