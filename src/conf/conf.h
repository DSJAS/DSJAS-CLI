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

#include "DSJAS.h"

#ifndef __CONF_H__
#define __CONF_H__

/* JSON */
json_value *json_findKey(char *key, json_value root);
bool json_keyExists(char *key, json_value root);
char *json_getString(json_value val);
long json_getInt(json_value val);
bool json_getBool(json_value val);

/* INI */
void ini_set(dictionary *ini, const char *section, const char *key,
			 const char *val);
void ini_serialise(dictionary *ini, FILE *f);

/* DSJAS */
void init_configs(DSJAS *state);
void destroy_configs(DSJAS *state);

#endif // CONF_H
