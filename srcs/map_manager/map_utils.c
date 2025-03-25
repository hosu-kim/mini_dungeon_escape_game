/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/25 17:41:27 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/** 
 * @note
 * 1. 맵이 사각형인가 검사; 겸 맵 세로 길이도 구조체에 저장.
 * 2. 이 함수에서 높이와 너비를 저장함.
 * 3. t_map 구조체는 맵의 정보를 담고 있음
 * 4. The first while loop counts width
 * 5. and in the next line, it saves the width in map_info
 * 6. second while,.height
 * */
int	check_retangular(char **map, t_map *map_info)
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map[0][width] && map[0][width] != '\n')
		width++;
	map_info->width = width;
	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width] && map[height][width] != '\n')
			width++;
		if (width != map_info->width)
		{
			ft_putstr_fd("Error: the map is not rectangular.\n", 2);
			return (0);
		}
		height++;
	}
	map_info->height = height;
	return (1);
}

/**
 * 첫번째 행이거나 마지막 행이거나, 첫번째 열이거나, 마지막 열이거나
 * 그 중에서 1이 아닐 때
 * 행을 먼저 정하고 열을 순회한다.
 */
int	check_walls(char **map, t_map *map_info)
{
	int	row_count;
	int	column_count;

	row_count = 1;
	while (row_count < map_info->height)
	{
		column_count = 1;
		while (column_count < map_info->width)
		{
			if ((row_count == 0 || row_count == map_info->height
					|| column_count == 0 || column_count == map_info->width)
				&& (map[row_count][column_count] != '1'))
			{
				ft_putstr_fd("Error: The map is not surrounded by walls.\n", 2);
				return (0);
			}
			column_count++;
		}
		row_count++;
	}
	return (1);
}

/**
 * 1. provided char is a desired char, saves it in map_info if not error
 */
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
	int	row_i;
	int	column_i;

	map_info->collectibles = 0;
	map_info->exit = 0;
	map_info->player = 0;
	row_i = 0;
	while (row_i < map_info->height)
	{
		column_i = 0;
		while (column_i < map_info->width)
		{
			if (!check_valid_char(map[row_i][column_i], map_info))
				return (0);
			column_i++;
		}
		row_i++;
	}
	if (map_info->collectibles < 1 || map_info->exit != 1
		|| map_info->player != 1)
	{
		ft_putstr_fd("Error: Map elements are incorrect.\n", 2);
		return (0);
	}
	return (1);
}

/**
 * check_valid_path()->map_path.c
 */
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
