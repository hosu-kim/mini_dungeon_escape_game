/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/28 20:22:07 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_valid_move(t_game_resources *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width || new_y < 0 \
		|| new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

static void	collect_item(t_game_resources *game, int x, int y)
{
	if (game->map[y][x] == 'C')
	{
		game->collected++;
		game->map[y][x] = '0';
	}
}

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
