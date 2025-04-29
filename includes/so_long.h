/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:25:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/29 14:01:39 by hoskim           ###   ########seoul.kr  */
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
}	t_map_info;

/* function prototypes */

//event_setup.c
int		key_press(int keycode, t_game_resources *game_resources);

//game_env_setup.c
void	init_game_resources(t_game_resources *game_resources, \
	char **map_data_storage, t_map_info *map_info);
void	end_game(t_game_resources *game_resources, int success);
int		create_window(t_game_resources *game_resources);
int		close_window(t_game_resources *game);
int		check_exit(t_game_resources *game, int x, int y);

// rendering_setup.c
void	load_game_images(t_game_resources *game);
void	render_map(t_game_resources *game);

// get_map_data.c
int		read_map_file(char *filename);
void	store_line_into_storage(char **map_storage, int line_count, int fd);
char	**get_map_data(char *filepath);

// if_valid_path.c
int		if_valid_path(char **map, t_map_info *map_info);

// mpa_elements.c
void	find_player_position(char **map_data_storage, int *x, int *y);

//map_reading.c
char	*get_a_line_from_fd(int fd);
int		count_lines_of_map(char *filename);
char	**copy_map(char **map, t_map_info *map_info);

// validate_map_data.c
int		validate_map_data(char **map, t_map_info *map_info);

// ft_put_utils.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

//ft_str_utils.c
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);

//memory_deallocation.c 
void	free_map_data_storage(char **map_data_storage);
void	exit_game(t_game_resources *game);

#endif
