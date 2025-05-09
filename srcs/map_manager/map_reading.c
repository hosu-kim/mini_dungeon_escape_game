/*
file: srcs/map_manager/map_reading.c
description: Provides utility functions for reading map files line by line,
			 counting lines, and creating deep copies of map data.
			 These functions are fundamental for processing
			 and manipulating the game map.
author: hosu-kim
created: 2025/03/08 10:38:27 UTC
*/

#include "mini_dungeon_escape.h"

/**
 * @brief Appends a character from the buffer to the string.
 * @note Takes a pointer to a string pointer that is allocated
 *  in the calling function.
 */
static int	append_char_to_line(char **dest_string, char buffer[2])
{
	char	*old_string;

	old_string = *dest_string;
	*dest_string = ft_strjoin(*dest_string, buffer);
	free(old_string);
	if (!*dest_string)
		return (0);
	return (1);
}

/**
 * @brief Reads a line from the given file descriptor.
 * @details
 * ============================== Code flow ==============================
 *    1. Memory allocaion to result_line.
 *    2. Read the first character.
 *    3. while(1): the chracter is valid and not a newline.
 *       (1): Append a character to result_line
 *       (2): Reads the new character
 *    4. if(2): if nothing to read, free memory.
 *    5. Returns result_line
 * @note
 * - File descriptor remembers its read position.
 */
char	*get_a_line_from_fd(int fd)
{
	char	char_buffer[2];
	char	*result_line;
	int		read_remaining;

	result_line = malloc(sizeof(char) * 1);
	if (!result_line)
		return (0);
	result_line[0] = '\0';
	read_remaining = read(fd, char_buffer, 1);
	char_buffer[1] = '\0';
	while (read_remaining > 0 && char_buffer[0] != '\n')
	{
		if (!append_char_to_line(&result_line, char_buffer))
			return (0);
		read_remaining = read(fd, char_buffer, 1);
		char_buffer[1] = '\0';
	}
	if (read_remaining <= 0 && result_line[0] == '\0')
	{
		free(result_line);
		return (0);
	}
	return (result_line);
}

/**
 * @brief Counts the number of lines of a map
 * @details
 * ============================== Code flow ==============================
 * 1. while: Counts lines up to the last line
 * 2. Returns number of the lines
 */
int	count_lines_of_map(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = read_map_file(filename);
	if (fd == -1)
		return (-1);
	line_count = 0;
	line = get_a_line_from_fd(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_a_line_from_fd(fd);
	}
	close(fd);
	return (line_count);
}

static char	*copy_line(char *line, int width)
{
	char	*line_copy;
	int		i;

	line_copy = malloc(sizeof(char) * (width + 1));
	if (!line_copy)
		return (NULL);
	i = 0;
	while (i < width)
	{
		line_copy[i] = line[i];
		i++;
	}
	line_copy[i] = '\0';
	return (line_copy);
}

/**
 * @note
 * 	1. allocate_copy_line()->map_path_validator_helpers.c
 * 	2. Size of all pointer variables are 8 bytes in 64 bit
 *  3. (map_info->height + 1): 1 for NULL pointer
 */
char	**copy_map(char **map, t_map_info *map_info)
{
	char	**map_copy;
	int		i;

	map_copy = malloc(sizeof(char *) * (map_info->height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < map_info->height)
	{
		map_copy[i] = copy_line(map[i], map_info->width);
		if (!map_copy[i])
		{
			free_map_data_storage(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}
