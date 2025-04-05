/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path_validator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:46 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/05 11:40:23 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * @note
 * 	1. allocate_copy_line()->map_path_validator_helpers.c
 * 	2. Size of all pointer variables are 8 bytes in 64 bit
 *  3. (map_info->height + 1): 1 for NULL pointer
 */
char	**copy_map(char **map, t_map *map_info)
{
	char	**copy_map;
	int		height_i;

	copy_map = malloc(sizeof(char *) * (map_info->height + 1));
	if (!copy_map)
		return (NULL);
	height_i = 0;
	while (height_i < map_info->height)
	{
		copy_map[height_i] = copy_line(map[height_i], map_info->width);
		if (!copy_map[height_i])
		{
			free_map_data_storage(copy_map);
			return (NULL);
		}
		height_i++;
	}
	copy_map[height_i] = NULL;
	return (copy_map);
}

int	check_valid_path(char **map, t_map *map_info)
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
	counts_elements(map_copy, &copy_map_info);
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
