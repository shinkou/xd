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
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "xd.h"

/**
 * Show bytes as hexidecimals in file
 * @param ptr pointer to a xd options struct
 */
static int dump_file(const xdopts * const ptr)
{
	char *buf = 0;
	unsigned long long wk = 0, idx = 0;
	long cnt = 0, i = 0;
	ssize_t ret = 0;
	off_t fsize = 0;
	short addrwidth = 2;
	char addrfmt[16] = {0,};

	if (0 >= ptr->fd) return -1;

	wk = fsize = lseek(ptr->fd, 0, SEEK_END);

	idx = (0 > ptr->offset)
		? (0 > fsize + ptr->offset ? 0 : fsize + ptr->offset)
		: ptr->offset;

	while((wk >>= 8) & 0xff) addrwidth += 2;

	if (0 < ptr->limit && (idx + ptr->limit < fsize))
		fsize = idx + ptr->limit;

	sprintf(addrfmt, "%%0%dx:", addrwidth);

	buf = calloc(1, ptr->bytes_per_read);

	for
	(
		lseek(ptr->fd, idx, SEEK_SET);
		(ret = read(ptr->fd, buf, ptr->bytes_per_read)) > 0 && fsize > idx;
	)
	{
		for(wk = 0; wk < ret && fsize > idx; wk += cnt)
		{
			cnt = (ptr->bytes_per_line <= (ret - wk))
				? ptr->bytes_per_line : ret - wk;

			printf(addrfmt, idx);

			for(i = 0; i < cnt && fsize > idx; i++)
			{
				printf(" %02hhx", buf[wk + i]);
				idx++;
			}

			printf("\n");
		}
	}

	free(buf);

	return ret;
}

/**
 * Show bytes as hexidecimals in stdin
 * @param ptr pointer to a xd options struct
 */
static int dump_stdin(const xdopts * const ptr)
{
	char *buf = 0;
	unsigned long long int wk = 0, idx = 0;
	int cnt = 0, i = 0;
	ssize_t ret = 0;

	buf = calloc(1, ptr->bytes_per_read);

	while((ret = read(ptr->fd, buf, ptr->bytes_per_read)) > 0)
	{
		for(wk = 0; wk < ret; wk += cnt)
		{
			cnt = (ptr->bytes_per_line <= (ret - wk)) ? ptr->bytes_per_line : ret - wk;

			printf("%08x:", idx);
			for(i = 0; i < cnt; i++) printf(" %02hhx", buf[wk + i]);
			printf("\n");

			idx += cnt;
		}
	}

	free(buf);

	return ret;
}

/**
 * Process argument
 * @param ptr pointer to a xd options struct
 * @return zero: normal finish; non-zero: error
 */
int xd(xdopts * const ptr)
{
	if (0 < ptr->fd)
		return dump_file(ptr);
	else
		return dump_stdin(ptr);
}
