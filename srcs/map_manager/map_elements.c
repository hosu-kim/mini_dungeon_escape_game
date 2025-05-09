/*
file: srcs/map_manager/map_elements.c
description: Provides functionality to locate specific elements within
			 the game map, such as finding the player's starting position.
author: hosu-kim
created: 2025/03/08 14:13:44 UTC
*/

#include "mini_dungeon_escape.h"

void	find_player_position(char **map_data_storage, int *x, int *y)
{
	int	height;
	int	width;

	height = 0;
	while (map_data_storage[height])
	{
		width = 0;
		while (map_data_storage[height][width])
		{
			if (map_data_storage[height][width] == 'P')
			{
				*x = width;
				*y = height;
				return ;
			}
			width++;
		}
		height++;
	}
}
