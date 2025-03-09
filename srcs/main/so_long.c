/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:48:07 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 20:04:21 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;
	t_map	map_info;
	char	**map;

	if (argc != 2)
	{
		ft_putstr_fd("Error: input only one file name.\n", 2);
		return (1);
	}
	map = read_map(argv[1]);
	if (!map)
		return (1);
	if (!validate_map(map, &map_info))
	{
		free_map(map);
		return (1);
	}
	init_game(&game, map, &map_info);
	if (!create_window(&game))
		return (1);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	render_map(&game);
	mlx_loop(game.mlx);
	return (0);
}
