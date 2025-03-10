// debug_map_elements.c
#include <stdio.h>
#include "so_long.h"

void debug_count_elements(char **map, t_map *map_info)
{
    int i, j;
    
    map_info->collectibles = 0;
    map_info->exit = 0;
    map_info->player = 0;
    
    i = 0;
    while (i < map_info->height)
    {
        j = 0;
        while (j < map_info->width)
        {
            char current = map[i][j];
            if (current == 'C')
                map_info->collectibles++;
            else if (current == 'E')
                map_info->exit++;
            else if (current == 'P')
                map_info->player++;
            j++;
        }
        i++;
    }
    printf("디버그: Collectibles=%d, Exit=%d, Player=%d\n",
            map_info->collectibles, map_info->exit, map_info->player);
}