/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:36:30 by hoskim            #+#    #+#             */
/*   Updated: 2025/03/05 17:34:33 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx_win;
	t_data	img;
	void	*mlx;
	int		width;
	int		height;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	width = 800;
	while (width <= 1000)
	{
		my_mlx_pixel_put(&img, width, 300, 0x00FF0000);
		width++;
	}
	width = 800;
	while (width <= 1000)
	{
		my_mlx_pixel_put(&img, width, 500, 0x00FF0000);
		width++;
	}
	height = 500;
	while (height >= 300)
	{
		my_mlx_pixel_put(&img, 800, height, 0x00FF0000);
		height--;
	}
	height = 500;
	while (height >= 300)
	{
		my_mlx_pixel_put(&img, 1000, height, 0x00FF0000);
		height--;
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
