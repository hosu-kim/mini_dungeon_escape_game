/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/26 20:07:25 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
 * - File descriptors remembers its read position.
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
