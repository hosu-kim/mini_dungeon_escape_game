/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_deallocation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:25:04 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/26 22:18:23 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

/**
 * @brief Frees all memory allocated for a 2D character array
 *        First frees each string, then frees the pointer array itself.
 */
void	free_map_data_storage(char **map_data_storage)
{
	int	i;

	if (!map_data_storage)
		return ;
	i = 0;
	while (map_data_storage[i])
	{
		free(map_data_storage[i]);
		map_data_storage[i] = NULL;
		i++;
	}
	free(map_data_storage);
}

static void	free_images(t_game_resources *game)
{
	if (game->img_player)
		mlx_destroy_image(game->graphic_system, game->img_player);
	if (game->img_wall)
		mlx_destroy_image(game->graphic_system, game->img_wall);
	if (game->img_collectible)
		mlx_destroy_image(game->graphic_system, game->img_collectible);
	if (game->img_exit)
		mlx_destroy_image(game->graphic_system, game->img_exit);
	if (game->img_floor)
		mlx_destroy_image(game->graphic_system, game->img_floor);
}

void	exit_game(t_game_resources *game)
{
	static int	already_exited = 0;

	if (already_exited)
		return ;
	already_exited = 1;
	if (!game)
		return ;
	free_images(game);
	if (game->window)
		mlx_destroy_window(game->graphic_system, game->window);
	if (game->graphic_system)
		mlx_destroy_display(game->graphic_system);
	if (game->map)
	{
		free_map_data_storage(game->map);
		game->map = NULL;
	}
	if (game->graphic_system)
		free(game->graphic_system);
	exit(0);
}
