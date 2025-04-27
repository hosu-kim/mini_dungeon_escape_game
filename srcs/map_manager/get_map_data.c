/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:36:50 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/27 14:51:10 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Checks if extension is ".ber"
 * @details 
 * - Codeflow
 * 	1. while(1): Counts length of file name
 * 	2. if(1): length is 4 or less -> return (0)
 * 	3. else if(1): last 4 characters are not ".ber" -> return (0)
 * 	4. If file extension is ".ber" -> return (1)
 */
static int	check_file_extension(char *filename)
{
	int	len;

	len = 0;
	while (filename[len])
		len++;
	if (len <= 4)
		return (0);
	else if (filename[len - 4] != '.' || filename[len - 3] != 'b'
		|| filename[len - 2] != 'e' || filename[len - 1] != 'r')
		return (0);
	return (1);
}

/**
 * @brief Opens map file
 * @details
 * - Codeflow
 *   1. check_file_extention()
 *    (1) If error -> return -1 (-1 to send error as fd)
 *   2. Open(pathname, flags): O_RDONLY(Open for reading only),
 *                             Error -> return (-1)
 *   3. Return the fd
 */
int	read_map_file(char *filename)
{
	int	fd;

	if (!check_file_extension(filename))
	{
		ft_putstr_fd("Error: Bad extension\n", 2);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: Failed to open file\n", 2);
		return (-1);
	}
	return (fd);
}

void	store_line_into_storage(char **map_storage, int line_count, int fd)
{
	char	*line;
	int		i;

	line = get_a_line_from_fd(fd);
	i = 0;
	while (line != NULL && i < line_count)
	{
		map_storage[i++] = line;
		line = get_a_line_from_fd(fd);
	}
	map_storage[i] = NULL;
	close(fd);
}

/**
 * @brief
 * @details
 * ============================== Codeflow ==============================
 *  1. count_map_lines(): counts how many lines in map (.ber)
 *  2. read map file(): Returns a file descriptor.
 *  3. Allocates memomry to map_data: + 1 for a NULL pointer
 *  4. store_line_into_storage()
 */
char	**get_map_data(char *filepath)
{
	int		fd;
	char	**map_data_storage;
	int		line_count;

	line_count = count_lines_of_map(filepath);
	if (line_count <= 0)
	{
		ft_putstr_fd("Error: The map is empty\n", 2);
		return (0);
	}
	fd = read_map_file(filepath);
	if (fd == -1)
		return (0);
	map_data_storage = malloc(sizeof(char *) * (line_count + 1));
	if (!map_data_storage)
		return (0);
	store_line_into_storage(map_data_storage, line_count, fd);
	return (map_data_storage);
}
