/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 19:27:43 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		end_game(game, 0);
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}

static int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->width || new_y < 0 || new_y >= game->height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	if (game->map[new_y][new_x] == 'E' \
		&& game->collectibles_collected < game->collectibles)
		return (0);
	return (1);
}

static void	collect_item(t_game *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collectibles_collected++;
		game->map[y][x] = '0';
	}
}

void	move_player(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (!is_valid_move(game, new_x, new_y))
		return ;
	game->map[game->player_y][game->player_x] = '0';
	collect_item(game, new_x, new_y);
	if (check_exit(game, new_x, new_y))
		return ;
	game->player_x = new_x;
	game->player_y = new_y;
	game->map[game->player_y][game->player_x] = 'P';
	game->moves++;
	render_map(game);
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(game->moves, 1);
	ft_putstr_fd("\n", 1);
}
