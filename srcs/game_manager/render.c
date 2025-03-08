/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:39:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 16:48:27 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_xpm_image(void *mlx, char *path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, path, width, height);
	if (!img)
	{
		ft_putstr_fd("Error: image loading failed.\n", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
		return (NULL);
	}
	return (img);
}

void	load_images(t_game *game)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	game->img_player = load_xpm_image(game->mlx, "assets/player.xpm", \
										&width, &height);
	game->img_wall = load_xpm_image(game->mlx, "assets/wall.xpm", \
										&width, &height);
	game->img_collectible = load_xpm_image(game->mlx, "assets/collectible.xpm", \
											&width, &height);
	game->img_exit = load_xpm_image(game->mlx, "assets/ecit.xpm", \
									&width, &height);
	game->img_floor = load_xpm_image(game->mlx, "assets/floor.xpm", \
									&width, &height);
	if (!game->img_player || !game->img_wall || !game->img_collectible \
		|| !game->img_exit || !game->img_collectible)
		exit_game(game);
}

static void	draw_tile(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win, img, \
							x * TILE_SIZE, y * TILE_SIZE);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			draw_tile(game, game->img_floor, x, y);
			if (game->map[y][x] == '1')
				draw_tile(game, game->img_wall, x, y);
			else if (game->map[y][x] == 'C')
				draw_tile(game, game->img_collectible, x, y);
			else if (game->map[y][x] == 'E')
				draw_tile(game, game->img_exit, x, y);
			else if (game->map[y][x] == 'P')
				draw_tile(game, game->img_player, x, y);
			x++;
		}
		y++;
	}
	render_moves(game);
}

void	render_moves(t_game *game)
{
	char	*moves_str;
	char	*tmp;

	moves_str = ft_strjoin("Moves: ", "");
	tmp = moves_str;
	moves_str = ft_strjoin(moves_str, "0");
	free(tmp);
	mlx_string_put(game->mlx, game->win, 10, 20, 0xFFFFFF, moves_str);
	free(moves_str);
}
