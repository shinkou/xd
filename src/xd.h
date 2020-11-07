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
#ifndef XD_H
#define XD_H 1

typedef struct _xdopts
{
	int fd;
	long lines_per_read;
	long bytes_per_line;
	long bytes_per_read;
	long offset;
	long limit;
} xdopts;

int xd(xdopts * const);

#endif
