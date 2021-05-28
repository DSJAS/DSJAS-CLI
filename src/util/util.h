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

#include <stdbool.h>

#ifndef __UTIL_H__
#define __UTIL_H__

/* Terminal Colors */
#define TERMCOLOR_RED "\x1b[31m"
#define TERMCOLOR_GREEN "\x1b[32m"
#define TERMCOLOR_YELLOW "\x1b[33m"
#define TERMCOLOR_BLUE "\x1b[34m"
#define TERMCOLOR_MAGENTA "\x1b[35m"
#define TERMCOLOR_CYAN "\x1b[36m"
#define TERMCOLOR_RESET "\x1b[0m"

/* IO */
void wrn(char *msg);
void err(char *msg);
void msg(char *msg);
void inf(char *msg);
void win(char *msg);

void out_msg(char *msg);
void out_put(char *msg);

/* FILEIO */
char *path_addFile(const char *path, const char *file);
long file_getSize(const char *path);

#endif // UTIL_H
