/*
file: srcs/main/main.c
description: Implements the main game execution logic and entry point
			 for Mini Dungeon Escape. 
			 This includes initializing the game environment, loading resources,
			 handling the game loop, and processing command-line arguments.
author: hosu-kim
created: 2025/04/21 13:41:09 UTC
*/

#include "mini_dungeon_escape.h"

/**
 * @brief Executes the components of the game.
 * @details
 * ------------------------------ Code Flow ------------------------------
 * 1. mlx_init(): Prepares the graphic system for running the game.
 * 2. init_game_resources(): Copies map and map_info into map_data_storage.
 * 3. create_window()
 * 4. load_game_images()
 * 5. render_map()
 * 6. mlx_hook(win: window pointer,
 *             event: event number,
 *             mask: event maks(Keyboard input, mouse click, etc.),
 *             callback: a function to be executed,
 *             param: param to be input to the function
 *    )
 *    : Prepares clsoing the window(17 means X button in X11)
 * 7. mlx_key_hook(): Specifies a function to be executed when keys are pressed.
 * 8. mlx_loop(): Keeps the windows open
 */
char	game_execution(t_map_info map_info, char **map_data_storage)
{
	t_game_resources	game_resources;

	game_resources.graphic_system = mlx_init();
	if (!game_resources.graphic_system)
	{
		free_map_data_storage(game_resources.map);
		game_resources.map = NULL;
		putstr_fd("Error: Graphic system preparation failed.\n", 2);
		return (0);
	}
	init_game_resources(&game_resources, map_data_storage, &map_info);
	if (!create_window(&game_resources))
	{
		free_map_data_storage(game_resources.map);
		game_resources.map = NULL;
		putstr_fd("Error: Window creation failed.\n", 2);
		return (0);
	}
	load_game_images(&game_resources);
	render_map(&game_resources);
	mlx_hook(game_resources.window, 17, 0, close_window, &game_resources);
	mlx_key_hook(game_resources.window, key_press, &game_resources);
	mlx_loop(game_resources.graphic_system);
	return (1);
}

/**
 * @brief Entry point of the program.
 * @details
 * ------------------------------ Code Flow ------------------------------
 * 1. get_map_data(): Copies the data from argv[1]
 * 2. validate_map_data(): Validates the data.
 * 3. game_execution(): Executes the game.
 */
int	main(int argc, char *argv[])
{
	t_map_info			map_info;
	char				**map_data_storage;

	if (argc != 2)
	{
		putstr_fd("Usage: ./so_long <map_file_path>\n", 2);
		return (1);
	}
	map_data_storage = get_map_data(argv[1]);
	if (!map_data_storage)
	{
		putstr_fd("Error: Failed to read map\n", 2);
		return (1);
	}
	if (!validate_map_data(map_data_storage, &map_info))
	{
		free_map_data_storage(map_data_storage);
		return (1);
	}
	if (!game_execution(map_info, map_data_storage))
	{
		free_map_data_storage(map_data_storage);
		return (1);
	}
	return (0);
}
