/*
file: srcs/game_manager/game_env_setup.c
description: Initialize game resources, create the window, 
			 and handle game termination.
author: hosu-kim
created: 2025/03/08 10:39:09 UTC
*/

#include "mini_dungeon_escape.h"

/**
 * @brief   Initialize the game resources from map metadata and raw map data.
 * @param   game_resources   Pointer to the game resources structure to set up.
 * @param   map_data_storage 2D array of map characters.
 * @param   map_info         Metadata about the map 
 *                           (width, height, collectible count).
 *
 * - Assigns map_data_storage to game_resources->map.
 * - Sets map dimensions (map_width, map_height).
 * - Records total collectibles and resets collected count to zero.
 * - Resets move counter to zero.
 * - Finds and stores the player’s starting coordinates.
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
	find_player_position(map_data_storage, \
						&game_resources->player_x, &game_resources->player_y);
}

/**
 * @brief   Display final game result, free resources, and exit.
 * @param   game_resources    Pointer to the game resources structure.
 * @param   success           Flag indicating if the game was cleared (1) 
 *                            or aborted (0).
 *
 * - Prints a success or termination message.
 * - Outputs the total number of moves.
 * - Calls exit_game() to clean up graphics and memory.
 * - Terminates the process.
 */
void	end_game(t_game_resources *game_resources, int success)
{
	if (success)
		putstr_fd("\nGame clear! You escaped the dungeon.\n", 1);
	else
		putstr_fd("\nGame ended.\n", 1);
	putstr_fd("Total moves: ", 1);
	putnbr_fd(game_resources->moves, 1);
	putstr_fd("\n", 1);
	exit_game(game_resources);
	exit(0);
}

/**
 * @brief   Create a MiniLibX window sized to fit the map.
 * @param   game_resources    Pointer to the game resources structure.
 * @return  int               Returns 1 on success, 0 on failure.
 *
 * - Calculates window width and height by multiplying map dimensions 
 *   by TILE_SIZE.
 * - Calls mlx_new_window() to open the window.
 * - On failure, calls exit_game() to release resources and returns 0.
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
 * @brief   Callback for window close event in MiniLibX.
 * @param   game    Pointer to the game resources structure.
 * @return  int     Always returns 0.
 *
 * - Invokes end_game() to cleanly terminate the game when the window is closed.
 */
int	close_window(t_game_resources *game)
{
	end_game(game, 0);
	return (0);
}

/**
 * @brief   Check if the player stepped on the exit tile
 *          with all items collected.
 * @param   game    Pointer to the game resources structure.
 * @param   x       The x-coordinate of the player's new position.
 * @param   y       The y-coordinate of the player's new position.
 * @return  int     Returns 1 if exit conditions are met (triggers game end),
 *                  otherwise 0.
 *
 * - Verifies that map[y][x] is 'E' and collected == collectibles.
 * - Calls end_game() with success if conditions match.
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
