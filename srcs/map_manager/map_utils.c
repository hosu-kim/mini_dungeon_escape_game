/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/06 22:48:47 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/*Checks if a map is rectangular.*/
int	check_rectangualr(char **map, t_map *map_info)
{
	int	i;
	int	width;

	i = 0;
	width = 0;
	while (map[0][width] && map[0][width] != '\n')
		width++;
	map_info->width = width;
	i = 0;
	while (map[i])
	{
		width = 0;
		while (map[i][width] && map[i][width] != '\n')
			width++;
		if (width != map_info->width)
		{
			write(0, "Error: The maps is not rectangular.\n", 36);
			return (0);
		}
		i++;
	}
	map_info->height = i;
	return (1);
}

int	check_walls(char **map, t_map *map_info)
{
	int	height_index;
	int	width_index;

	height_index = 0;
	while (height_index < map_info->height)
	{
		width_index = 0;
		while (width_index < map_info->width)
		{
			if ((height_index == 0 || height_index == map_info->height - 1 || \
					width_index == 0 || width_index == map_info->width - 1) \ 
					&& map[height_index][width_index] != '1')
			{
				write(0, "Error: The map is not surrounded by walls.\n", 43);
				return (0);
			}
			width_index++;
		}
		height_index++;
	}
	return (1);
}
