/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:38:27 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/08 19:30:45 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	append_char_to_line(char **line, char buffer[2])
{
	char	*temp;

	temp = *line;
	*line = ft_strjoin(*line, buffer);
	free(temp);
	if (!*line)
		return (0);
	return (1);
}

char	*read_line(int fd)
{
	char	buffer[2];
	char	*line;
	int		bytes_read;

	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	bytes_read = read(fd, buffer, 1);
	buffer[1] = '\0';
	while (bytes_read > 0 && buffer[0] != '\n')
	{
		if (!append_char_to_line(&line, buffer))
			return (NULL);
		bytes_read = read(fd, buffer, 1);
		buffer[1] = '\0';
	}
	if (bytes_read <= 0 && line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open_map_file(filename);
	if (fd == -1)
		return (-1);
	line_count = 0;
	line = read_line(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = read_line(fd);
	}
	close(fd);
	return (line_count);
}