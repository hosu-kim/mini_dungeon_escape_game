/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:09 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/10 17:09:55 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game, char **map, t_map *map_info)
{
	game->map = map;
	game->collectibles = map_info->collectibles;
	game->collectibles_collected = 0;
	game->moves = 0;
	game->player_x = map_info->player_x;
	game->player_y = map_info->player_y;
	game->exit_x = map_info->exit_x;
	game->exit_y = map_info->exit_y;
	find_player_position(map, &game->player_x, &game->player_y);
	load_images(game);
}

static void	calc_window_size(t_game *game, int *width, int *height)
{
	*width = game->width * TILE_SIZE;
	*height = game->height * TILE_SIZE;
}

void	restart_game(t_game *game)
{
	game->collectibles_collected = 0;
	game->moves = 0;
	find_player_position(game->map, &game->player_x, &game->player_y);
	render_map(game);
}

void	end_game(t_game *game, int success)
{
	if (success)
		ft_putstr_fd("\nGame clear! You got all \
					collectibles and escaped.\n", 1);
	else
		ft_putstr_fd("\nGame ended.\n", 1);
	ft_putstr_fd("Whole moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
	exit_game(game);
	exit(0);
}

void	setup_game(t_game *game)
{
	int	win_width;
	int	win_height;

	calc_window_size(game, &win_width, &win_height);
	render_map(game);
}
