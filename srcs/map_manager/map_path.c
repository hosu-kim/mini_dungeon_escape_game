/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:46 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 20:30:58 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map, t_map *map_info)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (map_info->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map_info->height)
	{
		copy[i] = malloc(sizeof(char) * (map_info->width + 1));
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		j = 0;
		while (j < map_info->width)
		{
			copy[i][j] = map[i][j];
			j++;
		}
		copy[i][j] = '\0';
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	count_elements(char **map_copy, t_map *map_info)
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

static void	flood_fill(char **map, int x, int y, t_map *map_info)
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
	flood_fill(map, x, y -1, map_info);
}

static int	check_path_result(char **map_copy, t_map *check_map)
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

/* 유효한 경로가 있는지 확인 */
int	check_valid_path(char **map, t_map *map_info)
{
	int		player_x;
	int		player_y;
	char	**map_copy;
	t_map	check_map;

	check_map.width = map_info->width;
	check_map.height = map_info->height;
	map_copy = copy_map(map, map_info);
	if (!map_copy)
		return (0);
	count_elements(map_copy, &check_map);
	find_player_position(map_copy, &player_x, &player_y);
	if (player_x == -1 || player_y == -1)
	{
		ft_putstr_fd("Error: Player position not found.\n", 2);
		free_map(map_copy);
		return (0);
	}
	flood_fill(map_copy, player_x, player_y, &check_map);
	return (check_path_result(map_copy, &check_map));
}
