/*
file: srcs/rendering_setup.c
description: Load XPM assets and render the game map and move counter.
author: hosu-kim
created: 2025/03/08 11:39:30
*/
#include "so_long.h"

static void	*load_xpm_to_image(void *mlx, char *xpm_path, int *w, int *h)
{
	void	*img;

	img = mlx_xpm_file_to_image(mlx, xpm_path, w, h);
	if (!img)
	{
		ft_putstr_fd("Error: image loading failed.\n", 2);
		ft_putstr_fd(xpm_path, 2);
		ft_putstr_fd("\n", 2);
		exit_game(NULL);
	}
	return (img);
}

void	load_game_images(t_game_resources *game)
{
	int	w;
	int	h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	game->img_player = load_xpm_to_image(game->graphic_system, \
										"assets/player.xpm", &w, &h);
	game->img_wall = load_xpm_to_image(game->graphic_system, \
										"assets/wall.xpm", &w, &h);
	game->img_collectible = load_xpm_to_image(game->graphic_system, \
										"assets/collectible.xpm", &w, &h);
	game->img_exit = load_xpm_to_image(game->graphic_system, \
										"assets/exit.xpm", &w, &h);
	game->img_floor = load_xpm_to_image(game->graphic_system, \
										"assets/floor.xpm", &w, &h);
}

static void	draw_tile(t_game_resources *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->graphic_system, game->window, \
							img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_moves(t_game_resources *game)
{
	char	*num;
	char	*str;

	num = ft_itoa(game->moves);
	str = ft_strjoin("Moves: ", num);
	free(num);
	mlx_string_put(game->graphic_system, game->window, 10, 20, 0xFFFFFF, str);
	free(str);
}

void	render_map(t_game_resources *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			draw_tile(game, game->img_floor, x, y);
			if (game->map[y][x] == '1')
				draw_tile(game, game->img_wall, x, y);
			else if (game->map[y][x] == 'C')
				draw_tile(game, game->img_collectible, x, y);
			else if (game->map[y][x] == 'E')
				draw_tile(game, game->img_exit, x, y);
			if (game->player_x == x && game->player_y == y)
				draw_tile(game, game->img_player, x, y);
			x++;
		}
		y++;
	}
	render_moves(game);
}
