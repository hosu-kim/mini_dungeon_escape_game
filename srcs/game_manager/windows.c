/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:11:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 20:04:03 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_window(t_game *game)
{
	int	win_width;
	int	win_height;

	win_width = game->width * TILE_SIZE;
	win_height = game->height * TILE_SIZE;
	game->win = mlx_new_window(game->mlx, win_width, win_height, "so_long");
	if (!game->win)
	{
		exit_game(game);
		return (0);
	}
	return (1);
}

int	close_window(t_game *game)
{
	end_game(game, 0);
	return (0);
}

int	check_exit(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'E' \
		&& game->collectibles_collected == game->collectibles)
	{
		end_game(game, 1);
		return (1);
	}
	return (0);
}
