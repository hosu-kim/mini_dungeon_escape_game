/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/06 19:57:05 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/** 
 * @brief check if every line has the same num of chars as the first line.
 * @details
 * - Codeflow
 * 1. while(1): Counts width of the first line and stores it into map_info
 * 2. while(2): Counts height
 *    (a) while & if: compares every line if it has the same width 
 *                    as the first line.
 * 3. Stores height into map_info.
 * */
int	if_rectangular(char **map, t_map *map_info)
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
 * @brief Checks if all edges of map are filled with '1'
 * @details
 * - Codeflow
 *     1. while(1st): counts row until the end.
 *         (1) counts column until the end in every row.
 *         (2) if count is in the first or the last row
 *             of the first or the last column
 *             and it doesn't have 1 -> return 0
 *     2. If walls enclose -> Return 1
 */
int	if_walls_enclose(char **map, t_map *map_info)
{
	int	row_count;
	int	column_count;

	row_count = 0;
	while (row_count < map_info->height)
	{
		column_count = 0;
		while (column_count < map_info->width)
		{
			if ((row_count == 0 || row_count == map_info->height - 1
					|| column_count == 0 || column_count == map_info->width - 1)
				&& (map[row_count][column_count] != '1'))
			{
				ft_putstr_fd("Error: The walls don't enclose the map.\
->if_walls_enclose()\n", 2);
				return (0);
			}
			column_count++;
		}
		row_count++;
	}
	return (1);
}

/**
 * @brief Checks if provided character is valid for the game (C/E/P/0/1)
 *        and stores it into the corresponding member of structure.
 */
static int	if_a_valid_element_and_store(char c, t_map *map_info)
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

/**
 * @brief Checks all character are valid for the game.
 * @details
 * - Codeflow
 * 1. Initializes members of provided structure
 * 2. while(1): Counts rows until the height of map
 *     (1) while: Counts rows until the width in every row count
 *     (2) if: Checks if not a valid character -> return (0)
 * 3. if: Checks if map doesn't have
 *     (1) At least one 'C'(collectables)
 *     (2) Only one 'E'(exit)
 *     (3) Only one 'P'(player)
 *     -> return (0)
 * 4. all char valid -> return (1);
 */
int	if_valid_elements(char **map, t_map *map_info)
{
	int	row_index;
	int	column_index;

	map_info->collectibles = 0;
	map_info->exit = 0;
	map_info->player = 0;
	row_index = 0;
	while (row_index < map_info->height)
	{
		column_index = 0;
		while (column_index < map_info->width)
		{
			if (!if_a_valid_element_and_store(map[row_index][column_index], map_info))
				return (0);
			column_index++;
		}
		row_index++;
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
 * 
 */
int	validate_map_data(char **map, t_map *map_info)
{
	if (!map)
		return (0);
	if (!if_rectangular(map, map_info))
		return (0);
	if (!if_walls_enclose(map, map_info))
		return (0);
	if (!if_valid_elements(map, map_info))
		return (0);
	if (!if_valid_path(map, map_info))
		return (0);
	ft_putstr_fd("Map validation check completed: The map is valid.\n", 1);
	return (1);
}
