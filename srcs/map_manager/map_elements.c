/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:13:44 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/28 18:36:28 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player_position(char **map_data_storage, int *x, int *y)
{
	int	height;
	int	width;

	height = 0;
	while (map_data_storage[height])
	{
		width = 0;
		while (map_data_storage[height][width])
		{
			if (map_data_storage[height][width] == 'P')
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
