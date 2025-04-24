/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:41:09 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/22 01:05:27 by hoskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	game_execution(t_map_info map_info, char **map_data_storage)
{
	t_game_resources	game_resources;

	game_resources.graphics = mlx_init();
	if (!game_resources.graphics)
	{
		free_map_data_storage(game_resources.map);
		game_resources.map = NULL;
		ft_putstr_fd("Error: game graphic initialization failed.\n", 2);
		return (0);
	}
	init_game_resources(&game_resources, map_data_storage, &map_info);
	if (!create_window(&game_resources))
	{
		free_map_data_storage(game_resources.map);
		game_resources.map = NULL;
		ft_putstr_fd("Error: Window creation failed.\n", 2);
		return (0);
	}
	load_game_images(&game_resources);
	render_map(&game_resources);
	mlx_hook(game_resources.win, 17, 0, close_window, &game_resources);
	mlx_key_hook(game_resources.win, key_press, &game_resources);
	mlx_loop(game_resources.graphics);
	return (1);
}

/**
 * @brief Entry point of the program.
 * @details
 * ------------------------------ Code Flow ------------------------------
 * 1. Copies the data from the provided map data file.
 * 2. Validates the data if it's valid for running the game.
 * 3. Prepares graphic resources for running the game.
 * 4. Creates a window for the gaming environment.
 */
int	main(int argc, char *argv[])
{
	t_map_info			map_info;
	char				**map_data_storage;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file_path>\n", 2);
		return (1);
	}
	map_data_storage = get_map_data(argv[1]);
	if (!map_data_storage)
	{
		ft_putstr_fd("Error: Failed to read map.\n", 2);
		return (1);
	}
	if (!validate_map_data(map_data_storage, &map_info))
	{
		free_map_data_storage(map_data_storage);
		map_data_storage = NULL;
		return (1);
	}
	if(!game_execution(map_info, map_data_storage))
	{
		free_map_data_storage(map_data_storage);
		map_data_storage = NULL;
		return (1);
	}
	return (0);
}
