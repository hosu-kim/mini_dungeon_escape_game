/*
file: srcs/utils/put_utils.c
description: Contains utility functions for outputting characters, strings,
			 and integers to a specified file descriptor.
			 These are general-purpose printing functions used
			 throughout the application.
author: hosu-kim
created: 2025/03/08 10:40:09 UTC
*/

#include "mini_dungeon_escape.h"

static void	putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/**
 * @details Prints the provided string to the file descriptor.
 */
void	putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	while (*s)
	{
		putchar_fd(*s, fd);
		s++;
	}
}

/**
 * @brief Prints an integer after converting to characters.
 * @details
 * - Codeflow
 *     1. if(1): Detects INT_MIN
 *     2. if(2): Determines negative sign and print it.
 */
void	putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		putchar_fd('-', fd);
		n = -n;
	}
	if (n >= 10)
	{
		putnbr_fd(n / 10, fd);
		putnbr_fd(n % 10, fd);
	}
	else
		putchar_fd(n + '0', fd);
}
