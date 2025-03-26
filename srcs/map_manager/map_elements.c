/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:13:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/26 20:39:56 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/// @brief 
/// @param map 
/// @param x 
/// @param y 
void	find_player_position(char **map, int *x, int *y)
{
	int	height;
	int	width;

	height = 0;
	while (map[height])
	{
		width = 0;
		while (map[height][width])
		{
			if (map[height][width] == 'P')
			{
				*x = width;
				*y = height;
				return ;
			}
			width++;
		}
		height++;
	}
}
