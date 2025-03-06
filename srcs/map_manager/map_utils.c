/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/06 22:39:04 by hoskim           ###   ########seoul.kr  */
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
	int	i;
	int	j;

	i = 0;
	while (i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			if ((i == 0 || ))
		}
	}
}
