/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:46 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/09 19:30:00 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*allocate_copy_line(char *src, int width)
{
	char	*line;
	int		j;

	line = malloc(sizeof(char) * (width + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < width)
	{
		line[j] = src[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

void	count_elements(char **map_copy, t_map *map_info)
{
	int	i;
	int	j;

	map_info->collectibles = 0;
	map_info->exit = 0;
	i = 0;
	while (map_copy[i])
	{
		j = 0;
		while (map_copy[i][j])
		{
			if (map_copy[i][j] == 'C')
				map_info->collectibles++;
			else if (map_copy[i][j] == 'E')
				map_info->exit++;
			j++;
		}
		i++;
	}
}

void	flood_fill(char **map, int x, int y, t_map *map_info)
{
	if (x < 0 || y < 0 || x >= map_info->width || y >= map_info->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		map_info->collectibles--;
	else if (map[y][x] == 'E')
		map_info->exit--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, map_info);
	flood_fill(map, x - 1, y, map_info);
	flood_fill(map, x, y + 1, map_info);
	flood_fill(map, x, y - 1, map_info);
}

int	check_path_result(char **map_copy, t_map *check_map)
{
	if (check_map->collectibles > 0 || check_map->exit > 0)
	{
		ft_putstr_fd("Error: Not all collectibles or exit are reachable.\n", 2);
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}
