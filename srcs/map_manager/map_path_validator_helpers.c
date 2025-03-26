/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_validator_helpers.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:46 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/26 20:40:28 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/// @brief 
/// @param line 
/// @param width 
/// @return 
char	*copy_line(char *line, int width)
{
	char	*copy_line;
	int		width_i;

	copy_line = malloc(sizeof(char) * (width + 1));
	if (!copy_line)
		return (NULL);
	width_i = 0;
	while (width_i < width)
	{
		copy_line[width_i] = line[width_i];
		width_i++;
	}
	copy_line[width_i] = '\0';
	return (copy_line);
}

void	counts_elements(char **map_copy, t_map *map_info)
{
	int	height;
	int	width;

	map_info->collectibles = 0;
	map_info->exit = 0;
	height = 0;
	while (map_copy[height])
	{
		width = 0;
		while (map_copy[height][width])
		{
			if (map_copy[height][width] == 'C')
				map_info->collectibles++;
			else if (map_copy[height][width] == 'E')
				map_info->exit++;
			width++;
		}
		height++;
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
