/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:22:01 by tmalidi           #+#    #+#             */
/*   Updated: 2024/03/21 15:11:56 by tmalidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	draw_floor(t_data *gd)
{
	int			i;
	int			j;
	uint32_t	sky;
	uint32_t	floor;

	i = 0;
	sky = convert_into_hexa(gd->sky_color);
	floor = convert_into_hexa(gd->floor_color);
	while (i < WINDOW_WIDTH)
	{
		j = 0;
		while (j < WINDOW_HEIGHT / 2)
			put_pixel_to_image(gd, i, j++, sky);
		while (j < WINDOW_HEIGHT)
			put_pixel_to_image(gd, i, j++, floor);
		i++;
	}
}

void	draw_vertical_line(t_data *game_data, t_ray_data *ray)
{
	float	height;
	int		i;
	int		pixel;
	float	ray_angle;

	if (ray->dist == -1)
		return ;
	ray_angle = (ray->id / (float)WINDOW_WIDTH - 0.5) * (69 * M_PI / 180);
	height = (100 * WINDOW_HEIGHT) / (ray->dist * cos(ray_angle));
	if (height >= 1080)
		height = 1080;
	i = 0;
	while (i < height)
	{
		if (!collision(game_data,ray->x, ray->y - 1) && !collision(game_data,ray->x, ray->y + 1))
		{
			if (!collision(game_data,ray->x + 1, ray->y))
				pixel = BLACK_COLOR;//get_pixel_color(game_data, 0, i / height * 1080, ray->y  % 72);
			else
				pixel = BLUE_COLOR;
		}
		else
			if (!collision(game_data,ray->x, ray->y + 1))
				pixel = ORANGE_COLOR;
			else
				pixel = MAGENTA_COLOR;
			//pixel = get_pixel_color(game_data, 0, i / height * 1080, ray->x  % 72);
		put_pixel_to_image(game_data, (WINDOW_WIDTH / 1920) * ray->id ,
			((WINDOW_HEIGHT / 2) - height / 2) + i, pixel);
		i++;
	}
}

void	put_pixel_to_image(t_data *gd, int x, int y, int color)
{
	char	*dst;

	dst = gd->pixel.addr + (y * gd->pixel.line_length
			+ x * (gd->pixel.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_data *gd, int x, int y, int ray)
{
	char	*dst;

	dst = gd->tex.addr[ray] + (y * gd->tex.line_length
			+ x * (gd->tex.bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
