/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 02:38:40 by jrenault          #+#    #+#             */
/*   Updated: 2024/01/27 19:09:20 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	my_mlx_pixel_put(t_pixel *pixel, int x, int y, int color)
{
	char	*dst;

	dst = pixel->addr + (y * pixel->line_length + x
			* (pixel->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_square_put(t_pixel *pixel, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < pixel->size)
	{
		j = 0;
		while (j < pixel->size)
		{
			my_mlx_pixel_put(pixel, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	my_mlx_circle_put(t_pixel *pixel, int center_x, int center_y, int color)
{
	int	x;
	int	y;
	int	i;
	int	radius_error;

	x = pixel->radius;
	y = 0;
	radius_error = 1 - x;
	while (x >= y)
	{
		i = center_x - x;
		while (i <= center_x + x)
		{
			my_mlx_pixel_put(pixel, i, center_y + y, color);
			my_mlx_pixel_put(pixel, i, center_y - y, color);
			i++;
		}
		i = center_x - y;
		while (i <= center_x + y)
		{
			my_mlx_pixel_put(pixel, i, center_y + x, color);
			my_mlx_pixel_put(pixel, i, center_y - x, color);
			i++;
		}
		y++;
		if (radius_error < 0)
			radius_error += 2 * y + 1;
		else
		{
			x--;
			radius_error += 2 * (y - x + 1);
		}
	}
}

int	show_minimap(t_data *param)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	param->pixel.img = mlx_new_image(param->mlx,
			400, 400);
	param->pixel.addr = mlx_get_data_addr(param->pixel.img, &param->pixel.bits_per_pixel,
			&param->pixel.line_length, &param->pixel.endian);
	while (param->map[y])
	{
		while (param->map[y][x])
		{
			if (param->map[y][x] == '1')
				my_mlx_square_put(&param->pixel, (x * param->pixel.size), (y * param->pixel.size), RED_COLOR);
			if (param->map[y][x] == 'N')
			{
				param->map[y][x] = '0';
				param->pos_x = x;
				param->pos_y = y;
			}
			x++;
		}
		x = 0;
		y++;
	}
	my_mlx_circle_put(&param->pixel, (param->pos_x * param->pixel.size + param->pixel.radius), (param->pos_y * param->pixel.size + param->pixel.radius), BLUE_COLOR);
	mlx_put_image_to_window(param->mlx, param->win, param->pixel.img, 0, 0);
	return (0);
}
