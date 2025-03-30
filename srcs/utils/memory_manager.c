/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:25:04 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/30 18:56:34 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

/**
 * @brief Frees all memory allocated for a 2D character array
 *        First frees each string, then frees the pointer array itself.
 */
void	free_map_storage(char **map_storage)
{
	int	i;

	if (!map_storage)
		return ;
	i = 0;
	while (map_storage[i])
	{
		free(map_storage[i]);
		map_storage[i] = NULL;
		i++;
	}
	free(map_storage);
}

static void	free_images(t_game *game)
{
	if (game->img_player)
		mlx_destroy_image(game->mlx, game->img_player);
	if (game->img_wall)
		mlx_destroy_image(game->mlx, game->img_wall);
	if (game->img_collectible)
		mlx_destroy_image(game->mlx, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->mlx, game->img_exit);
	if (game->img_floor)
		mlx_destroy_image(game->mlx, game->img_floor);
}

void	exit_game(t_game *game)
{
	static int	already_exited = 0;

	if (already_exited)
		return ;
	already_exited = 1;
	if (!game)
		return ;
	free_images(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->map)
	{
		free_map_storage(game->map);
		game->map = NULL;
	}
	exit(0);
}
