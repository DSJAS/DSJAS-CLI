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
#include "util.h"

extern global_options gOpts;

static void init_global(DSJAS *state);
static void init_theme(DSJAS *state);
static void init_module(DSJAS *state);
static void init_extension(DSJAS *state);
static void init_version(DSJAS *state);

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
	char *gfn = path_addFile(gOpts.path, "Config.ini");
	char *tfn = path_addFile(gOpts.path, "admin/site/UI/config.ini");
	char *mfn = path_addFile(gOpts.path, "admin/site/UI/config.ini");
	char *efn = path_addFile(gOpts.path, "admin/site/UI/config.ini");

	FILE *gf = fopen(gfn, "r+");
	FILE *tf = fopen(tfn, "r+");
	FILE *mf = fopen(mfn, "r+");
	FILE *ef = fopen(efn, "r+");

	ini_serialise(state->config.glb, gf);
	ini_serialise(state->config.thm, tf);
	ini_serialise(state->config.mod, mf);
	ini_serialise(state->config.ext, ef);

	iniparser_freedict(state->config.glb);
	iniparser_freedict(state->config.thm);
	iniparser_freedict(state->config.mod);
	iniparser_freedict(state->config.ext);

	json_value_free(state->version.vers);
	fclose(state->version.versConfig);

	fclose(gf);
	fclose(tf);
	fclose(mf);
	fclose(ef);

	free(gfn);
	free(tfn);
	free(mfn);
	free(efn);
}

static void init_global(DSJAS *state)
{
	char *filename = path_addFile(gOpts.path, "Config.ini");
	state->config.glb = iniparser_load(filename);

	free(filename);
}

static void init_theme(DSJAS *state)
{
	char *filename = path_addFile(gOpts.path, "admin/site/UI/config.ini");
	state->config.thm = iniparser_load(filename);

	free(filename);
}

static void init_module(DSJAS *state)
{
	char *filename = path_addFile(gOpts.path, "admin/site/UI/config.ini");
	state->config.mod = iniparser_load(filename);

	free(filename);
}

static void init_extension(DSJAS *state)
{
	state->config.extension.placeholder = 'A';
}

static void init_version(DSJAS *state)
{
	char *filename = path_addFile(gOpts.path, "Version.json");
	FILE *f = fopen(filename, "r+");

	if (!f) {
		err("Failed to open version config file");
		exit(-1);
	}

	state->version.versConfig = f;
	long len = file_getSize(filename);

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

	free(filename);
	free(cont);
}
