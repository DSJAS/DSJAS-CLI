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

#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "util/util.h"
#include "conf.h"

json_value *json_findKey(char *key, json_value root)
{
	if (root.type != json_object) {
		wrn("Attempted to find key in non-object");
		return NULL;
	}

	for (unsigned int i = 0; i < root.u.object.length; i++) {
		if (strcmp(root.u.object.values[i].name, key) == 0) {
			return root.u.object.values[i].value;
		}
	}

	return NULL;
}

bool json_keyExists(char *key, json_value root)
{
	if (root.type != json_object) {
		wrn("Attempted to find key in non-object");
		return false;
	}

	for (unsigned int i = 0; i < root.u.object.length; i++) {
		if (strcmp(root.u.object.values[i].name, key)) {
			return true;
		}
	}

	return false;
}

char *json_getString(json_value val)
{
	switch (val.type) {
	case json_none:
		wrn("Null value where a string was expected");
		return "";
	case json_object:
		wrn("Invalid JSON conversion");
		return "";
	case json_array:
		wrn("Invalid JSON conversion");
		return "";
	case json_boolean:
		return (val.u.boolean) ? "true" : "false";
	case json_string:
		return val.u.string.ptr;
	case json_integer: {
		int b10 = log10(val.u.integer);
		char *res = malloc(sizeof(char) * b10);
		snprintf(res, b10, "%li", val.u.integer);
		return res;
	}
	case json_double: {
		char *res = malloc(sizeof(char) * 4096);
		snprintf(res, 4096, "%f", val.u.dbl);
		return res;
	}
	default:
		wrn("Unknown JSON object type");
		return "";
	}
}

long json_getInt(json_value val)
{
	switch (val.type) {
	case json_none:
		wrn("Null value where an integer was expected");
		return 0;
	case json_object:
		wrn("Invalid JSON conversion");
		return 0;
	case json_array:
		wrn("Invalid JSON conversion");
		return 0;
	case json_boolean:
		return val.u.boolean;
	case json_string:
		return strtol(val.u.string.ptr, NULL, 10);
	case json_integer:
		return val.u.integer;
	case json_double: {
		wrn("Converting a double to an integer. Precision may be "
		    "lost.");
		double initial = strtod(val.u.string.ptr, NULL);
		return (long)initial;
	}
	default:
		wrn("Unknown JSON object type");
		return 0;
	}
}

bool json_getBool(json_value val)
{
	switch (val.type) {
	case json_none:
		wrn("Null value where a boolean was expected");
		return false;
	case json_object:
		wrn("Invalid JSON conversion");
		return false;
	case json_array:
		wrn("Invalid JSON conversion");
		return false;
	case json_boolean:
		return val.u.boolean;
	case json_string:
		if (strcmp(val.u.string.ptr, "true") == 0) {
			return true;
		} else {
			return false;
		}
	case json_integer:
		return val.u.integer;
	case json_double: {
		return (int)val.u.dbl;
	}
	default:
		wrn("Unknown JSON object type");
		return false;
	}
}
