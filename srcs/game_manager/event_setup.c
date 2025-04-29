/*
file: srcs/event_setup.c
description: Handle player movement logic, item collection, exit checks,
             and key-press events.
author: hosu-kim
created: 2025/03/08 11:39:47
*/
#include "so_long.h"

/**
 * @brief Check if the target position is within bounds and not a wall.
 * @details
 *   - Validates that (new_x, new_y) lies inside the map dimensions.
 *   - Ensures the tile at the destination is not '1' (wall).
 * @param  game  Pointer to the game resources containing map data.
 * @param  new_x X-coordinate of the intended move.
 * @param  new_y Y-coordinate of the intended move.
 * @return int   1 if movement is valid; 0 otherwise.
 */
static int	is_valid_move(t_game_resources *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width || new_y < 0 \
		|| new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

/**
 * @brief Collect an item on the map if present at the specified tile.
 * @details
 *   - If the tile contains 'C', increments game->collected count.
 *   - Marks the tile as empty ('0') after collection.
 * @param game Pointer to the game resources containing map data.
 * @param x    X-coordinate of the tile.
 * @param y    Y-coordinate of the tile.
 */
static void	collect_item(t_game_resources *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collected++;
		game->map[y][x] = '0';
	}
}

/**
 * @brief Move the player and handle game-state updates.
 * @details
 *   - Calculates the new position based on (dx, dy).
 *   - Checks validity of move; exits early if invalid.
 *   - Collects any item at the destination.
 *   - Checks for exit condition (tile 'E' and all collectibles gathered).
 *     - Calls end_game() on success.
 *   - Updates player coordinates and increments move counter.
 *   - Re-renders the map and prints the current move count to stdout.
 * @param game Pointer to the game resources.
 * @param dx   Change in X direction (-1, 0, +1).
 * @param dy   Change in Y direction (-1, 0, +1).
 */
void	move_player(t_game_resources *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y))
		return ;
	collect_item(game, new_x, new_y);
	if (game->map[new_y][new_x] == 'E' && game->collected == game->collectibles)
	{
		end_game(game, 1);
		return ;
	}
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	render_map(game);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
}

/**
 * @brief Handle key-press events to move player or exit game.
 * @details
 *   - ESC: triggers immediate game end.
 *   - W/A/S/D: moves player up/left/down/right.
 *   - Always returns 0 per MLX hook convention.
 * @param  keycode        Key code of the pressed key.
 * @param  game_resources Pointer to the game resources.
 * @return int            Always 0.
 */
int	key_press(int keycode, t_game_resources *game_resources)
{
	if (keycode == KEY_ESC)
		end_game(game_resources, 0);
	else if (keycode == KEY_W)
		move_player(game_resources, 0, -1);
	else if (keycode == KEY_A)
		move_player(game_resources, -1, 0);
	else if (keycode == KEY_S)
		move_player(game_resources, 0, 1);
	else if (keycode == KEY_D)
		move_player(game_resources, 1, 0);
	return (0);
}
