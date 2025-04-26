/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:18:06 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/26 20:59:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/** 
 * @brief Checks if every line has the same num of chars as the first line.
 * @details
 * ============================== Codeflow ==============================
 * 1. while(1): Counts width of the first line and stores it into map_info
 * 2. while(2): Counts height
 *    (1) while & if: Compare every line if it has the same width
 *                    as the first line.
 * 3. Stores height into map_info.
 * */
int	if_rectangular(char **map, t_map_info *map_info)
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
			ft_putstr_fd("Error: The map is not rectangular", 2);
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
 *     1. while(1): Counts row until the end.
 *         while(2) Counts columns until the end in every row.
 *         if(1) If count is in the first or the last row
 *             of the first or the last column
 *             and it doesn't have 1 -> return(0)
 *     2. Walls enclose -> return(1)
 */
int	if_walls_enclose(char **map, t_map_info *map_info)
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
				ft_putstr_fd("Error: The walls don't enclose the map.\n", 2);
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
static int	if_a_valid_element_and_store(char c, t_map_info *map_info)
{
	if (c == 'C')
		map_info->collect++;
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
 * 1. while(1): Counts rows
 *     (1) while: Counts columns
 *     (2) if: not a valid character -> return (0)
 * 2. all char valid -> return (1);
 */
int	if_valid_elements(char **map, t_map_info *map_info)
{
	int	row_index;
	int	column_index;

	map_info->collect = 0;
	map_info->exit = 0;
	map_info->player = 0;
	row_index = 0;
	while (row_index < map_info->height)
	{
		column_index = 0;
		while (column_index < map_info->width)
		{
			if (!if_a_valid_element_and_store(map[row_index][column_index], \
				map_info))
				return (0);
			column_index++;
		}
		row_index++;
	}
	if (map_info->collect < 1 || map_info->exit != 1 || map_info->player != 1)
	{
		ft_putstr_fd("Error: Map elements are incorrect.\n", 2);
		return (0);
	}
	return (1);
}

/**
 * @brief Validates the map
 *        (1) If it's 'rectangular'
 *        (2) If the walls 'enclose' the map
 *        (3) If it has 'valid elements' (C, E, P, 0, 1)
 *        (4) If the 'path' is valid
 */
int	validate_map_data(char **map, t_map_info *map_info)
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
