/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 15:13:17 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_retangular(char **map, t_map *map_info)
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
			ft_putstr_fd("Error: the map is not rectangular.\n", 2);
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
			if ((i == 0 || i == map_info->height - 1 ||
				j == 0 || j == map_info->width - 1) && map[i][j] != '1')
			{
				ft_putstr_fd("Error: The map is not surrounded by walls.\n", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int	check_valid_char(char c, t_map *map_info)
{
	if (c == 'C')
		map_info->collectibles++;
	else if (c == 'E')
		map_info->exit++;
	else if (c == 'P')
		map_info->player++;
	else if (c != '0' && c != '1')
	{
		ft_putstr_fd("Error: An invalid character exists in the map\n", 2);
		return (0);
	}
	return (1);
}

int	check_elements(char **map, t_map *map_info)
{
	int	i;
	int	j;

	map_info->collectibles = 0;
	map_info->exit = 0;
	map_info->player = 0;
	i = 0;
	while (i < map_info->height)
	{
		j = 0;
		while (j < map_info->width)
		{
			if (!check_valid_char(map[i][j], map_info))
				return (0);
			j++;
		}
		i++;
	}
	if (map_info->collectibles < 1 || map_info->exit != 1 || map_info->player != 1)
	{
		ft_putstr_fd("Error: Map elements are incorrect.\n", 2);
		return (0);
	}
	return (1);
}

int	validate_map(char **map, t_map *map_info)
{
	if (!map)
		return (0);
	if (!check_retangular(map, map_info))
		return (0);
	if (!check_walls(map, map_info))
		return (0);
	if (!check_elements(map, map_info))
		return (0);
	if (!check_valid_path(map, map_info))
		return (0);
	ft_putstr_fd("Map validation check completed: The map is valid.\n", 1);
	return (1);
}