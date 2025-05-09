/*
file: srcs/map_manager/if_valid_path.c
description: Implements path validation for the game map using
			 a flood fill algorithm. It ensures that the player can reach
			 all collectibles and the exit from their starting position.
author: hosu-kim
created: 2025/03/08 10:38:46 UTC
*/

#include "mini_dungeon_escape.h"

static void	fill_map_structure(char **map_copy, t_map_info *map_info)
{
	int	height;
	int	width;

	map_info->collect = 0;
	map_info->exit = 0;
	height = 0;
	while (map_copy[height])
	{
		width = 0;
		while (map_copy[height][width])
		{
			if (map_copy[height][width] == 'C')
				map_info->collect++;
			else if (map_copy[height][width] == 'E')
				map_info->exit++;
			width++;
		}
		height++;
	}
}

static void	flood_fill(char **map, int x, int y, t_map_info *map_info)
{
	if (x < 0 || y < 0 || x >= map_info->width || y >= map_info->height)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		map_info->collect--;
	else if (map[y][x] == 'E')
		map_info->exit--;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, map_info);
	flood_fill(map, x - 1, y, map_info);
	flood_fill(map, x, y + 1, map_info);
	flood_fill(map, x, y - 1, map_info);
}

static int	check_path_result(char **map_copy, t_map_info *check_map)
{
	if (check_map->collect > 0 || check_map->exit > 0)
	{
		putstr_fd("Error: Not all collectibles or exit are reachable.\n", 2);
		free_map_data_storage(map_copy);
		return (0);
	}
	free_map_data_storage(map_copy);
	return (1);
}

int	if_valid_path(char **map, t_map_info *map_info)
{
	int			player_x;
	int			player_y;
	char		**map_copy;
	t_map_info	copy_of_map_info;

	copy_of_map_info.width = map_info->width;
	copy_of_map_info.height = map_info->height;
	map_copy = copy_map(map, map_info);
	if (!map_copy)
		return (0);
	fill_map_structure(map_copy, &copy_of_map_info);
	find_player_position(map_copy, &player_x, &player_y);
	if (player_x == -1 || player_y == -1)
	{
		putstr_fd("Error: Player position not found.\n", 2);
		free_map_data_storage(map_copy);
		return (0);
	}
	flood_fill(map_copy, player_x, player_y, &copy_of_map_info);
	return (check_path_result(map_copy, &copy_of_map_info));
}
