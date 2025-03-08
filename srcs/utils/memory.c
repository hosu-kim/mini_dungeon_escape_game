/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:40:47 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 18:25:26 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

static void	free_images(t_game *game)
{
	if (game->img_player)
		mlx_detroy_image(game->mlx, game->img_player);
	if (game->img_wall)
		mlx_detroy_image(game->mlx, game->img_wall);
	if (game->img_collectible)
		mlx_detory_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
}

void	exit_game(t_game *game)
{
	if (!game)
		return ;
	free_images(game);
	if (game->win)
		mlx_detroy_window(game->mlx, game->mlx);
	if (game->map)
		free_map(game->map);
	exit(0);
}
