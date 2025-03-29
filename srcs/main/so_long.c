/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:22:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/29 21:31:42 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map_info;
	char	**map_data;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./so_long <map_file>\n", 2);
		return (1);
	}
	map_data = get_map_data(argv[1]); // 문자열 배열 형식으로 맵 저장
	if (!map_data)
	{
		ft_putstr_fd("Error: Failed to read map.\n", 2); // 1. retangular 2. walls 3. elements 4. valid path -> map_utils.c
		return (1);
	}
	if (!validate_map_data(map_data, &map_info)) // map_utils.c
	{
		free_map(map_data);
		map_data = NULL;
		return (1);
	}
	game.map = map_data;
	game.height = 0;
	while (map_data[game.height])
		game.height++;
	game.width = 0;
	if (game.height > 0)
		game.width = ft_strlen(map_data[0]);
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
	init_game(&game, map_data, &map_info);
	render_map(&game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_key_hook(game.win, key_press, &game);
	mlx_loop(game.mlx);
	return (0);
}
