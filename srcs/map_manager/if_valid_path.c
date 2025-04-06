/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:46 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/06 20:49:50 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*copy_line(char *line, int width)
{
	char	*line_copy;
	int		index_w;

	line_copy = malloc(sizeof(char) * (width + 1));
	if (!line_copy)
		return (NULL);
	index_w = 0;
	while (index_w < width)
	{
		line_copy[index_w] = line[index_w];
		index_w++;
	}
	line_copy[index_w] = '\0';
	return (line_copy);
}

void	fill_map_structure(char **map_copy, t_map *map_info)
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
		free_map_data_storage(map_copy);
		return (0);
	}
	free_map_data_storage(map_copy);
	return (1);
}
/**
 * @note
 * 	1. allocate_copy_line()->map_path_validator_helpers.c
 * 	2. Size of all pointer variables are 8 bytes in 64 bit
 *  3. (map_info->height + 1): 1 for NULL pointer
 */
char	**copy_map(char **map, t_map *map_info)
{
	char	**map_copy;
	int		index_h;

	map_copy = malloc(sizeof(char *) * (map_info->height + 1));
	if (!map_copy)
		return (NULL);
	index_h = 0;
	while (index_h < map_info->height)
	{
		map_copy[index_h] = copy_line(map[index_h], map_info->width);
		if (!map_copy[index_h])
		{
			free_map_data_storage(map_copy);
			return (NULL);
		}
		index_h++;
	}
	map_copy[index_h] = NULL;
	return (map_copy);
}

int	if_valid_path(char **map, t_map *map_info)
{
	int		player_x;
	int		player_y;
	char	**map_copy;
	t_map	copy_map_info;

	copy_map_info.width = map_info->width;
	copy_map_info.height = map_info->height;
	map_copy = copy_map(map, map_info);
	if (!map_copy)
		return (0);
	store_elements_into_t_map(map_copy, &copy_map_info);
	find_player_position(map_copy, &player_x, &player_y);
	if (player_x == -1 || player_y == -1)
	{
		ft_putstr_fd("Error: Player position not found.\n", 2);
		free_map_data_storage(map_copy);
		return (0);
	}
	flood_fill(map_copy, player_x, player_y, &copy_map_info);
	return (check_path_result(map_copy, &copy_map_info));
}
