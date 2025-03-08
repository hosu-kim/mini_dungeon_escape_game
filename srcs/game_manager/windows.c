/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:11:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 17:15:12 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
