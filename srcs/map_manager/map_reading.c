/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:46:19 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/07 22:45:32 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/**
 * @note checks the file extension '.ber' 
 * 1. declares variable 'len' and initializes it with 0.
 * 2. iterates the filename array and count it with len. (while)
 * 3. checks if the characters of the extension exist in the filename (if)
 * 4. if OK, returns 1, not OK, returns 0.
 */
static int	file_extension_checker(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	if (filename[len - 1] != 'r' || filename[len - 2] != 'e' || \
			filename[len - 3] != 'b' || filename[len - 4] != '.')
		return (0);
	return (1);
}

static int	map_file_opener(char *filename)
{
	int	fd;

	if (!file_extension_checker(filename))
	{
		write(0, "Error: the file extension is not '.ber'.\n", 41);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(0, "Error: File open failure.\n", 26);
		return (-1);
	}
	return (fd);
}

static char	*line_reader(int fd)
{
	char	buffer[2];
	char	*line;
	char	*temp;
	int		bytes_read;

	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	bytes_read = read(fd, buffer, 1);
	buffer[1] = '\0';
	while (bytes_read > 0 && buffer[0] != '\n')
	{
		temp = line;
		line = ft_strjoin(line, buffer);
		free(temp);
		if (!line)
			return (NULL);
		bytes_read = read(fd, buffer, 1);
		buffer[1] = '\0';
	}
	if (bytes_read <= 0 && line[0] == '\0')
		return (free(line), NULL);
	return (line);
}

static int	line_counter(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = map_file_opener(filename);
	if (fd == -1)
		return (-1);
	line_count = 0;
	line = line_reader(fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

char	**map_reader(char *filename)
{
	int		fd;
	char	**map;
	char	*line;
	int		line_count;
	int		i;

	line_count = line_counter(filename);
	if (line_count <= 0)
	{
		write(0, "Error: The map is empty or failed to read.\n", 43);
		return (NULL);
	}
	fd = map_file_opener(filename);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	i = 0;
	line = line_reader(fd);
	while (line != NULL && i < line_count)
		map[i++] = line;
	map[i] = NULL;
	close(fd);
	return (map);
}
