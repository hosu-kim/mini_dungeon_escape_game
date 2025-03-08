/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:36:50 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 14:14:24 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	if (filename[len -1] != 'r' || filename[len - 2] != 'e' \
		|| filename[len - 3] != 'b' || filename[len - 4] != '.')
		return (0);
	return (1);
}

int	open_map_file(char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		ft_putstr_fd("Error: The file extension is not '.ber'.\n", 2);
		return (-1);
	}
}

char	**read_map(char *filename)
{
	int		fd;
	char	**map;
	char	*line;
	int		line_count;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
	{
		ft_putstr_fd("Error: The map is empty or cannot be read.\n", 2);
		return (NULL);
	}
	fd = open_map_file(filename);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	i = 0;
	line = read_line(fd);
	while (line != NULL && i < line_count)
		map[i++] = line;
	map[i] = NULL;
	close(fd);
	return (map);
}
