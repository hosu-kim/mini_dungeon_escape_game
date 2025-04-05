/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_map_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/05 19:33:41 by hoskim           ###   ########seoul.kr  */
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
 * @return A pointer to the resulting string containing the line, or NULL
 *         if no characters or memory allocation fails.
 * @details
 *  - Code flow
 *    1. Allocates memory for an empty string (result_line).
 *    2. Read the first character from the fd into char_buffer
 *    3. while: the chracter is valid and not a newline.
 *       (1): Append a character to result_line
 *       (2): Reads the new character into char_buffer
 *    4. if: if nothing to read, memory free, error handling.
 *    5. Returns result_line containing a line
 * @note
 *  * @note
 * - File descriptors keep their position:
 *   each read continues where previous read ended
 */
char	*get_line_from_fd(int fd)
{
	char	char_buffer[2];
	char	*result_line;
	int		read_count;

	result_line = malloc(sizeof(char) * 1);
	if (!result_line)
		return (NULL);
	result_line[0] = '\0';
	read_count = read(fd, char_buffer, 1);
	char_buffer[1] = '\0';
	while (read_count > 0 && char_buffer[0] != '\n')
	{
		if (!append_char_to_line(&result_line, char_buffer))
			return (NULL);
		read_count = read(fd, char_buffer, 1);
		char_buffer[1] = '\0';
	}
	if (read_count <= 0 && result_line[0] == '\0')
	{
		free(result_line);
		return (NULL);
	}
	return (result_line);
}

/**
 * 
 */
int	count_map_lines(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = read_map_file(filename);
	if (fd == -1)
		return (-1);
	line_count = 0;
	line = get_line_from_fd(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_line_from_fd(fd);
	}
	close(fd);
	return (line_count);
}
