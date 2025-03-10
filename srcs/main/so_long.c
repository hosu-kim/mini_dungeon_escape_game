/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 22:22:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/09 22:29:11 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
    t_game  game;
    t_map   map_info;
    char    **map;

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
    
    // Initialize window dimensions before creating the window
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
    
    // 여기에 MLX 이벤트 루프 및 후크를 추가합니다
    mlx_hook(game.win, 17, 0, close_window, &game);  // 창 닫기 버튼 처리
    mlx_key_hook(game.win, key_press, &game);       // 키보드 입력 처리
    mlx_loop(game.mlx);                             // 이벤트 루프 시작
    
    // exit_game(&game); - 이 부분은 제거합니다. close_window 함수에서 처리됨
    return (0);
}