/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 21:46:19 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/06 22:55:54 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len < 5)
		return (0);
	if (filename[len -4] != '.' || filename[len -3] != 'b' || \
			filename[len - 2] != 'e' || filename[len - 1] != 'r')
		return (0);
	return (1);
}

static int	open_map_file(char *filename)
{
	int	fd;

	if (!check_file_exension(filename))
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

static char	*read_line(int fd)
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
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static int	count_lines(char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	fd = open_map_file(filename);
	if (fd == -1)
		return (-1);
	line_count = 0;
	while ((line = read_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	close(fd);
	return (line_count);
}

char	**read_map(char *filename)
{
	int		fd;
	char	**map;
	char	*line;
	int		line_count;
	int		i;

	line_count = count_lines(filename);
	if (line_count <= 0)
	{
		write(0, "Error: The map is empty or failed to read.\n", 43);
		return (NULL);
	}
	fd = open_map_file(filename);
	if (fd == -1)
		return (NULL);
	map = malloc(sizeof(char *) * (line_count + 1));
	if (!map)
		return (NULL);
	i = 0;
	while ((line = read_line(fd)) != NULL && i < line_count)
		map[i++] = line;
	map[i] = NULL;
	close(fd);
	return (map);
}
