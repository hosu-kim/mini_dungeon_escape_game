/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/25 14:10:20 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
// 맵이 사각형인가 검사; 하는 겸 맵 세로 길이도 구조체에 저장.
// 이 함수에서 높이와 너비를 저장함.
int	check_retangular(char **map, t_map *map_info) // t_map 구조체는 맵의 정보를 담고 있음
{
	int	height;
	int	width;

	height = 0;
	width = 0;
	while (map[0][width] && map[0][width] != '\n') // 너비 측정
		width++;
	map_info->width = width; // 너비 저장
	height = 0;
	while (map[height]) // 높이 측정
	{
		width = 0;
		while (map[height][width] && map[height][width] != '\n')
			width++;
		if (width != map_info->width) // 첫번째 열에 행에 측정된 너비와 같지 않으면
		{
			ft_putstr_fd("Error: the map is not rectangular.\n", 2);
			return (0);
		}
		height++;
	}
	map_info->height = height; // 높이도 구조체에 저장
	return (1); // 참
}

int	check_walls(char **map, t_map *map_info)
{
	int	row_count;
	int	column_count;

	row_count = 1;
	while (row_count < map_info->height) // 행을 먼저 정하고 열을 순회한다.
	{
		column_count = 1;
		while (column_count < map_info->width)
		{
			// 첫번째 행이거나 마지막 행이거나, 첫번째 열이거나, 마지막 열이거나
			// 그 중에서 1이 아닐 때
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

static int	check_valid_element(char c, t_map *map_info)
{
	if (c == 'C') // 주어진 문자가 C(수집품)이면 맵 정보 구조체에 저장
		map_info->collectibles++;
	else if (c == 'E') // 주어진 문자가 E(출구)이면 맵 정보 구조체에 저장
		map_info->exit++;
	else if (c == 'P') // 주어진 문자가 P(플레이어)면 맵 정보 구조체에 저장
		map_info->player++;
	else if (c != '0' && c != '1') // 주어진 문자가 팔요한 문자가 아니면 
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
			if (!check_valid_element(map[i][j], map_info))
				return (0);
			j++;
		}
		i++;
	}
	if (map_info->collectibles < 1 || map_info->exit != 1
		|| map_info->player != 1)
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
