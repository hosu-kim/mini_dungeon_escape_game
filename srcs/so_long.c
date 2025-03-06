/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:24:54 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/06 18:24:37 by hoskim           ###   ########seoul.kr  */
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
		write(0, "Error: Please input only one map file.\n");
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
	init_game(&game, map);
	mlx_hook(game.window_instance, 2, 1L<<0, key_press, &game);
	mlx_hook(game.win, 17, 0, (int (*)())exit_game, &game);
	render_map(&game);
	mlx_loop(game.mlx);
	return (0);
}

void	exit_game(t_game *game)
{
	free_map(game->map);
	mlx_destroy_image(game->mlx_instance, game->img_player);
	mlx_destroy_image(game->mlx_instance, game->img_wall);
	mlx_destroy_image(game->mlx_instance, game->img_collectible);
	mlx_destroy_image(game->mlx_instance, game->img_exit);
	mlx_destroy_image(game->mlx_instance, game->img_floor);
	mlx_destroy_window(game->mlx_instance, game->window_instance);
	exit(0);
}

void	free_map(char **map)
{
	int	i;
	
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
}