/*
    xd - Hex Dump
    https://github.com/shinkou/xd/

    Copyright (C) 2020  Chun-Kwong Wong

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Check if input string is valid offset
 * @param str input string
 * @return 1: valid; 0: invalid
 */
int isoffset(const char * const str)
{
	char *s = 0;
	if (!str) return 0;
	for(s = (char *) str; *s; s++)
		if (!isdigit(*s) && ('-' != *s || s != str))
			return 0;
	return 1;
}

/**
 * Check if input string is valid number
 * @param str input string
 * @return 1: valid; 0: invalid
 */
int isnumber(const char * const str)
{
	char *s = 0;
	if (!str) return 0;
	for(s = (char *) str; *s; s++)
		if (!isdigit(*s))
			return 0;
	return 1;
}

/**
 * Read integer from input string and save it in output
 * @param str name of the number to read
 * @param in input string
 * @param out buffer for output
 * @return zero: normal finish; non-zero: error
 */
int readint(const char * const str, const char * const in, long *out)
{
	long l = strtol(in, 0, 10);
	if (errno)
	{
		if(str) printf("Invalid %s: %s\n", str, in);
		return 1;
	}
	else
	{
		if (out) *out = l;
	}
	return 0;
}
