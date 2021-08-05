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
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>

#include "util.h"

char *path_addFile(const char *path, const char *file)
{
	int pLen = strlen(path);
	int fLen = strlen(file);

	char *newPath = malloc(sizeof(char) * (pLen * fLen));
	strcpy(newPath, path);

	if (newPath[pLen - 1] != '/') {
		strcat(newPath, "/");
	}

	strcat(newPath, file);

	return newPath;
}

long file_getSize(const char *path)
{
	FILE *f = fopen(path, "rb");
	if (!f)
		return -1;

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);

	fclose(f);

	return fsize;
}

char *file_getContents(const char *path)
{
	FILE *f = fopen(path, "r");
	long size = file_getSize(path);

	if (!f) {
		return "";
	}

	char *cont = malloc(sizeof(char) * size);
	fread(cont, sizeof(char), size, f);

	fclose(f);
	return cont;
}

bool file_exists(const char *path)
{
	return !access(path, F_OK);
}

bool dir_exists(const char *path)
{
	DIR *dir = opendir(path);
	if (!dir) {
		return false;
	}

	closedir(dir);
	return true;
}
