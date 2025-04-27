/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_env_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:09 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/27 14:45:15 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Stores game data from map_info to game_resources
 */
void	init_game_resources(t_game_resources *game_resources, \
							char **map_data_storage, t_map_info *map_info)
{
	game_resources->map = map_data_storage;
	game_resources->map_height = map_info->height;
	game_resources->map_width = map_info->width;
	game_resources->collectibles = map_info->collect;
	game_resources->collected = 0;
	game_resources->moves = 0;
	game_resources->exit_x = map_info->exit_x;
	game_resources->exit_y = map_info->exit_y;
	find_player_position(map_data_storage, \
						&game_resources->player_x, &game_resources->player_y);
}

/**
 * @brief Ends game if the player successfully escapes.
 */
void	end_game(t_game_resources *game_resources, int success)
{
	if (success)
		ft_putstr_fd("\nGame clear! You escaped the dungeon.\n", 1);
	else
		ft_putstr_fd("\nGame ended.\n", 1);
	ft_putstr_fd("Total moves: ", 1);
	ft_putnbr_fd(game_resources->moves, 1);
	ft_putstr_fd("\n", 1);
	exit_game(game_resources);
	exit(0);
}

/**
 * @breif Creates a window for the game
 */
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

/**
 * @brief Wrapper function of end_game() for mlx_hook()
 */
int	close_window(t_game_resources *game)
{
	end_game(game, 0);
	return (0);
}

/**
 * @brief Checks if the player can exit the game at the given coorinates.(좌표)
 */
int	check_exit(t_game_resources *game, int x, int y)
{
	if (game->map[y][x] == 'E' && game->collected == game->collectibles)
	{
		end_game(game, 1);
		return (1);
	}
	return (0);
}
