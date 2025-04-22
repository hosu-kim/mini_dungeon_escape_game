/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:11:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/21 20:37:22 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_window(t_game_resources *game)
{
	int	win_width;
	int	win_height;

	win_width = game->map_width * TILE_SIZE;
	win_height = game->map_height * TILE_SIZE;
	game->win = mlx_new_window(game->graphics, win_width, win_height, "Mini Dungeon Escape");
	if (!game->win)
	{
		exit_game(game);
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
		game->collectibles_collected == game->collectibles)
	{
		end_game(game, 1);
		return (1);
	}
	return (0);
}
