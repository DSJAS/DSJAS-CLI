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

#include <stdlib.h>
#include <stdio.h>

#include "util/util.h"
#include "conf.h"

#include "iniparser.h"

void ini_set(dictionary *ini, const char *section, const char *key,
			 const char *val)
{
	char realKey[strlen(section) + strlen(key) + 1];
	sprintf(realKey, "%s:%s", section, key);

	iniparser_set(ini, realKey, val);
}

void ini_serialise(dictionary *ini, FILE *f)
{
	int count = iniparser_getnsec(ini);

	for (int c = 0; c < count; c++) {
		const char *sect = iniparser_getsecname(ini, c);
		int k = iniparser_getsecnkeys(ini, sect);

		char **keys = malloc(sizeof(char *) * k);
		iniparser_getseckeys(ini, sect, (const char **)keys);

		fprintf(f, "[%s]\n", sect);
		for (int i = 0; i < k; i++) {
			char *ind = strchr(keys[i], ':');

			fprintf(f, "%s=\"%s\"\n", ind + 1,
					iniparser_getstring(ini, keys[i], ""));
		}

		free(keys);
	}
}
