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
#include <stdbool.h>
#include <stdint.h>

#include "DSJAS.h"
#include "util.h"

extern global_options gOpts;

static void errms(char *msg, char del, char *col);
static void outms(char *msg);

void wrn(char *msg)
{
	errms(msg, '!', TERMCOLOR_YELLOW);
}

void err(char *msg)
{
	errms(msg, 'X', TERMCOLOR_RED);
}

void msg(char *msg)
{
	errms(msg, '*', TERMCOLOR_BLUE);
}

void inf(char *msg)
{
	errms(msg, 'I', TERMCOLOR_CYAN);
}

void win(char *msg)
{
	errms(msg, 'Y', TERMCOLOR_GREEN);
}

void out_msg(char *msg)
{
	if (!gOpts.quiet)
		outms(msg);
}

void out_msgc(char *msg, char *col)
{
	if (!gOpts.quiet) {
		char out[strlen(msg) + 2];

		sprintf(out, "%s%s%s", col, msg, TERMCOLOR_RESET);

		outms(out);
	} else {
		outms(msg);
	}
}

void out_log(char *msg)
{
	if (gOpts.verbose)
		outms(msg);
}

void out_put(char *msg)
{
	outms(msg);
}

static void outms(char *msg)
{
	fprintf(stdout, "%s", msg);
}

static void errms(char *msg, char del, char *col)
{
	fprintf(stderr, "[%s%c%s] %s\n", col, del, TERMCOLOR_RESET, msg);
}
