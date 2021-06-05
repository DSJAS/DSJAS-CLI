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
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "DSJAS.h"
#include "util.h"

extern global_options gOpts;

static void errms(const char *msg, const char del, const char *col);
static void outms(const char *msg);

void wrn(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	errms(out, '!', TERMCOLOR_YELLOW);
	free(out);
}

void err(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	errms(out, 'X', TERMCOLOR_RED);
	free(out);
}

void msg(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	errms(out, '*', TERMCOLOR_BLUE);
	free(out);
}

void inf(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	errms(out, 'I', TERMCOLOR_CYAN);
	free(out);
}

void win(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	errms(out, 'Y', TERMCOLOR_GREEN);
	free(out);
}

void out_msg(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	if (!gOpts.quiet)
		outms(out);

	free(out);
}

void out_msgc(const char *msg, const char *col, ...)
{
	char *fout;
	va_list args;
	va_start(args, col);
	vasprintf(&fout, msg, args);
	va_end(args);

	if (!gOpts.quiet) {
		char out[strlen(msg) + 2];

		sprintf(out, "%s%s%s", col, fout, TERMCOLOR_RESET);

		outms(out);
	} else {
		outms(fout);
	}

	free(fout);
}

void out_log(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	if (gOpts.verbose)
		outms(out);

	free(out);
}

void out_put(const char *msg, ...)
{
	char *out;
	va_list args;
	va_start(args, msg);
	vasprintf(&out, msg, args);
	va_end(args);

	outms(out);
	free(out);
}

static void outms(const char *msg)
{
	fprintf(stdout, "%s", msg);
}

static void errms(const char *msg, const char del, const char *col)
{
	fprintf(stderr, "[%s%c%s] %s\n", col, del, TERMCOLOR_RESET, msg);
}
