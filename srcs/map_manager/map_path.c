/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>         +#+  +:+       +#+        */
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

	copy = malloc(sizeof(char *) * (map_info->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map_info->height)
	{
		copy[i] = allocate_copy_line(map[i], map_info->width);
		if (!copy[i])
		{
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

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
