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
#include <fcntl.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <getopt.h>
#include "xd.h"
#include "utils.h"

#define BYTES_PER_LINE 16
#define LINES_PER_READ 512
#define OFFSET 0
#define LIMIT 0

/**
 * Print help message
 */
static void print_help()
{
	printf
	(
		"Usage:\n"
		"  xd [ OPTIONS ] FILE [ FILE [ FILE [ ... ] ] ]\n"
		"or\n"
		"  xd -\n\n"
		"Description:\n"
		"  Hex Dump\n\n"
		"OPTIONS:\n"
		"  -h\n"
		"      print out this help menu and quit\n"
		"  -b<NUM>, --bytes-per-line=<NUM>\n"
		"      number of bytes to display per line (default: %d)\n"
		"  -l<NUM>, --lines-per-read=<NUM>\n"
		"      number of lines per read (default: %d)\n"
		"  -O<NUM>, --offset=<NUM>\n"
		"      number of bytes to skip from the beginning (default: %d)\n"
		"  -L<NUM>, --limit=<NUM>\n"
		"      number of bytes to dump (default: %d, means no limit)\n\n"
		"where\n"
		"  NUM   an integer number\n"
		"  FILE  path of the file to dump\n"
		"  -     read from stdin\n\n"
		, BYTES_PER_LINE
		, LINES_PER_READ
		, OFFSET
		, LIMIT
	);
}

/**
 * Get XD options
 * @param argc argument count obtained from main function
 * @param argv pointer to arguments obtained from main function
 * @return zero: normal finish; non-zero: error
 */
static int getxdopts(int const argc, char * const *argv, xdopts * const xo)
{
	int c;

	static struct option long_opts[] =
	{
		{"help", 0, 0, 'h'}
		, {"bytes-per-line", 1, 0, 'b'}
		, {"lines-per-read", 1, 0, 'l'}
		, {"offset", 1, 0, 'O'}
		, {"limit", 1, 0, 'L'}
		, {0, 0, 0, 0}
	};

	while(-1 != (c = getopt_long(argc, argv, "O:L:b:l:h", long_opts, 0)))
	{
		switch(c)
		{
		case 'h':
			print_help();
			return 0;
			break;
		case 'L':
			if (!isnumber(optarg) || readint("limit", optarg, &xo->limit))
			{
				printf("Invalid limit: %s\n", optarg);
				return 1;
			}
			break;
		case 'O':
			if (!isoffset(optarg) || readint("offset", optarg, &xo->offset))
			{
				printf("Invalid offset: %s\n", optarg);
				return 1;
			}
			break;
		case 'b':
			if
			(
				!isnumber(optarg)
				|| readint("bytes_per_line", optarg, &xo->bytes_per_line)
			)
			{
				printf("Invalid bytes-per-line: %s\n", optarg);
				return 1;
			}
			xo->bytes_per_read = xo->bytes_per_line * xo->lines_per_read;
			break;
		case 'l':
			if
			(
				!isnumber(optarg)
				|| readint("lines_per_read", optarg, &xo->lines_per_read)
			)
			{
				printf("Invalid lines-per-read: %s\n", optarg);
				return 1;
			}
			xo->bytes_per_read = xo->bytes_per_line * xo->lines_per_read;
			break;
		case '?':
		default:
			printf("\n");
			print_help();
			return 1;
		}
	}

	if (optind == argc) print_help();

	return 0;
}

/**
 * Main function
 * @param argc argument count
 * @param argv arguments
 * @return zero: normal finish; non-zero: error
 */
int main(int const argc, char * const *argv)
{
	long idx = 0, ret = 0;
	xdopts xo =
	{
		0
		, LINES_PER_READ
		, BYTES_PER_LINE
		, LINES_PER_READ * BYTES_PER_LINE
		, OFFSET
		, LIMIT
	};

	if (ret = getxdopts(argc, argv, &xo)) return ret;

	for(idx = optind; idx < argc; idx++)
	{
		if (optind < idx) printf("\n");

		xo.fd = ('-' == argv[idx][0] && 0 == argv[idx][1])
			? STDIN_FILENO : open(argv[idx], O_RDONLY);

		if (0 > xo.fd)
		{
			perror(argv[idx]);
			printf("Error opening \"%s\".\n", argv[idx]);
			return 1;
		}
		else
		{
			if (ret = xd(&xo)) return ret;
		}

		if (0 < xo.fd) close(xo.fd);
	}

	return 0;
}
