/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 23:25:35 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/06 20:45:58 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define TILE_SIZE 32

// 키 코드 정의
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// 게임 데이터 구조체
typedef struct s_game_data
{
	void	*mlx_instance;
	void	*window_instance;
	char	**map;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		collectibles_collected;
	int		moves;
	void	*img_player;
	void	*img_wall;
	void	*img_collectible;
	void	*img_exit;
	void	*img_floor;
}	t_game;

typedef struct s_map_data
{
	char	**map;
	int		width;
	int		height;
	int		collectibles;
	int		exit;
	int		player;
	int		collectibles_found;
	int		exit_found;
}	t_map;

// 함수 프로토타입
char	**read_map(char *filename);
int		validate_map(char **map, t_map *map_info);
void	init_game(t_game *game, char **map);
void	load_images(t_game *game);
void	render_map(t_game *game);
int		key_press(int keycode, t_game *game);
void	move_player(t_game *game, int dx, int dy);
void	free_map(char **map);
void	exit_game(t_game *game);

#endif