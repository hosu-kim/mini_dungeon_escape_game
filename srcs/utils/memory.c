#include "so_long.h"
#include <stdlib.h>

void free_map(char **map)
{
    int i;

    if (!map)
        return;
    i = 0;
    while (map[i])
    {
        free(map[i]);
        map[i] = NULL;
        i++;
    }
    free(map);
}

static void free_images(t_game *game)
{
    if (game->img_player)
        mlx_destroy_image(game->mlx, game->img_player);
    if (game->img_wall)
        mlx_destroy_image(game->mlx, game->img_wall);
    if (game->img_collectible)
        mlx_destroy_image(game->mlx, game->img_collectible);
    if (game->img_exit)
        mlx_destroy_image(game->mlx, game->img_exit);
    if (game->img_floor)
        mlx_destroy_image(game->mlx, game->img_floor);
}

void exit_game(t_game *game)
{
    static int already_exited = 0;

    if (already_exited)
        return;
    already_exited = 1;
    if (!game)
        return;
    free_images(game);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    if (game->map)
    {
        free_map(game->map);
        game->map = NULL;  // 이후 중복 해제를 방지하기 위해 NULL로 설정
    }
    exit(0);
}