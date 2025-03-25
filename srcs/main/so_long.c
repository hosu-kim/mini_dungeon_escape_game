/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:22:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/24 16:33:49 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map_info;
	char	**map;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file>\n", 2);
		return (1);
	}
	map = read_map(argv[1]);
	if (!map)
	{
		ft_putstr_fd("Error: Failed to read map.\n", 2);
		return (1);
	}
	if (!validate_map(map, &map_info))
	{
		free_map(map);
		map = NULL;
		return (1);
	}
	game.map = map;
	game.height = 0;
	while (map[game.height])
		game.height++;
	game.width = 0;
	if (game.height > 0)
		game.width = ft_strlen(map[0]);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		free_map(game.map);
		game.map = NULL;
		ft_putstr_fd("Error: mlx initialization failed.\n", 2);
		return (1);
	}
	if (!create_window(&game))
	{
		free_map(game.map);
		game.map = NULL;
		ft_putstr_fd("Error: Window creation failed.\n", 2);
		return (1);
	}
	init_game(&game, map, &map_info);
	render_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
