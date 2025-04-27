/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:11:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/26 22:19:40 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_window(t_game_resources *game_resources)
{
	int	win_width;
	int	win_height;

	win_width = game_resources->map_width * TILE_SIZE;
	win_height = game_resources->map_height * TILE_SIZE;
	game_resources->window = mlx_new_window(game_resources->graphic_system, \
							 win_width, win_height, "Mini Dungeon Escape");
	if (!game_resources->window)
	{
		exit_game(game_resources);
		return (0);
	}
	return (1);
}

int	close_window(t_game_resources *game)
 {
 	end_game(game, 0);
 	return (0);
 }

int	check_exit(t_game_resources *game, int x, int y)
{
	if (game->map[y][x] == 'E' &&
		game->collected == game->collectibles)
	{
		end_game(game, 1);
		return (1);
	}
	return (0);
}
