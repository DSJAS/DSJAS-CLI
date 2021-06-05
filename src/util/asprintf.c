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
#include <stdarg.h>

#include "util.h"

int vasprintf(char **str, const char *fmt, va_list args)
{
	int s = 0;
	va_list tmp;

	va_copy(tmp, args);
	s = printflen(fmt, tmp);
	va_end(tmp);

	if (s < 0) {
		return -1;
	}

	*str = (char *)malloc(s + 1);

	if (NULL == *str) {
		return -1;
	}

	s = vsprintf(*str, fmt, args);
	return s;
}

int asprintf(char **str, const char *fmt, ...)
{
	int s = 0;

	va_list args;
	va_start(args, fmt);

	s = vasprintf(str, fmt, args);

	va_end(args);

	return s;
}

int printflen(const char *fmt, va_list args)
{
	return vsnprintf(NULL, 0, fmt, args);
}
