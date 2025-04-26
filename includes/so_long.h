/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:25:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/26 22:18:23 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define TILE_SIZE 32
// Definitions of the key codes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// Structure of the game resources
typedef struct s_game_resources
{
	void	*graphic_system;
	void	*window;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
	int		collectibles;
	int		collected;
	int		moves;
	void	*img_player;
	void	*img_wall;
	void	*img_collectible;
	void	*img_exit;
	void	*img_floor;
}	t_game_resources;

typedef struct s_map_data
{
	char	**map;
	int		width;
	int		height;
	int		collect;
	int		exit;
	int		player;
	int		exit_x;
	int		exit_y;
}	t_map_info;

/* function prototypes */

// map_data_reader.c
char	**get_map_data(char *filename);
int		read_map_file(char *filename);
char	**get_map_data(char *filename);

// map_reader.c
char	*get_a_line_from_fd(int fd);
int		count_lines_of_map(char *filename);

// map_utils.c
int		if_rectangular(char **map, t_map_info *map_info);
int		if_walls_enclose(char **map, t_map_info *map_info);
int		if_valid_elements(char **map, t_map_info *map_info);
int		validate_map_data(char **map, t_map_info *map_info);

// map_elements.c
void	find_player_position(char **map, int *x, int *y);

// map_path.c
int		if_valid_path(char **map, t_map_info *map_info);
char	**copy_map(char **map, t_map_info *map_info);

// map_path_helpers.c
char	*copy_line(char *src, int width);
void	flood_fill(char **map, int x, int y, t_map_info *map_info);
int		check_path_result(char **map_copy, t_map_info *check_map);

// game.c
void	init_game_resources(t_game_resources *game, char **map, \
							t_map_info *map_info);
void	restart_game(t_game_resources *game);
void	setup_game(t_game_resources *game);
void	end_game(t_game_resources *game, int success);

// render.c
void	load_game_images(t_game_resources *game);
void	render_map(t_game_resources *game);
void	render_moves(t_game_resources *game);

// events.c
int		key_press(int keycode, t_game_resources *game);
void	move_player(t_game_resources *game, int dx, int dy);

// window.c
int		create_window(t_game_resources *game);
int		close_window(t_game_resources *game);
int		check_exit(t_game_resources *game, int x, int y);

// utils.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// string_utils.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);

// memory_manager.c
void	free_map_data_storage(char **map);
void	exit_game(t_game_resources *game);

#endif
