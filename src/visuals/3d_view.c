/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_view.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 14:22:01 by tmalidi           #+#    #+#             */
/*   Updated: 2024/04/23 13:50:44 by tmalidi          ###   ########.fr       */
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

static int	give_color(t_data *game_data, t_ray_data *ray, int i, float height)
{
	if (!collision(game_data, ray->x + 1, ray->y))
		return (get_pixel_color(game_data, i
				/ height * WINDOW_HEIGHT, ray->y % TEX_SIDE, EA));
	else
		return (get_pixel_color(game_data, i
				/ height * WINDOW_HEIGHT, (TEX_SIDE - 1)
				- (ray->y % TEX_SIDE), WE));
	return (BLACK_COLOR);
}

void	draw_tex(t_data *game_data, t_ray_data *ray, int i, float height)
{
	int		pixel;

	pixel = -1;
	if (!collision(game_data, ray->x, ray->y - 1)
		&& !collision(game_data, ray->x, ray->y + 1))
	{
		pixel = give_color(game_data, ray, i, height);
	}
	else if (!collision(game_data, ray->x - 1, ray->y)
		&& !collision(game_data, ray->x + 1, ray->y))
	{
		if (!collision(game_data, ray->x, ray->y + 1))
			pixel = get_pixel_color(game_data, i
					/ height * WINDOW_HEIGHT, (TEX_SIDE - 1)
					- (ray->x % TEX_SIDE), SO);
		else
			pixel = get_pixel_color(game_data, i
					/ height * WINDOW_HEIGHT, ray->x % TEX_SIDE, NO);
	}
	if (pixel == -1)
		pixel = corner(game_data, ray, i, height);
	if (((WINDOW_HEIGHT / 2) - height / 2) + i <= 1080
		&& ((WINDOW_HEIGHT / 2) - height / 2) + i >= 0)
		put_pixel_to_image(game_data, game_data->c,
			((WINDOW_HEIGHT / 2) - height / 2) + i, pixel);
}

void	draw_vertical_line(t_data *game_data, t_ray_data *ray)
{
	double	height;
	double	new_dist;
	double	angle;

	if (ray->dist == -1)
		return ;
	if (ray->id > (WINDOW_WIDTH - 1) / 2)
		angle = game_data->angle * ((double)(WINDOW_WIDTH
					/ (double)2 - (double)ray->id));
	else
		angle = game_data->angle * ((((double)WINDOW_WIDTH
						- (double)ray->id)
					- ((double)WINDOW_WIDTH / (double)2)));
	new_dist = ray->dist * cos(angle);
	height = (100.0 * (double)WINDOW_HEIGHT) / (new_dist);
	game_data->c = anti_fisheye(ray, game_data);
	game_data->len = game_data->c - game_data->prev_column;
	draw_tex_process(game_data, height, ray);
	game_data->prev_column = game_data->c;
}

int	get_pixel_color(t_data *gd, int y, int ray, int card)
{
	char	*dst;

	dst = 0;
	if (card == NO)
	{
		dst = gd->tex_north.addr[ray] + (y * gd->tex_north.line_length
				+ 0 * (gd->tex_north.bits_per_pixel / 8));
	}
	if (card == SO)
	{
		dst = gd->tex_south.addr[ray] + (y * gd->tex_south.line_length
				+ 0 * (gd->tex_south.bits_per_pixel / 8));
	}
	if (card == EA)
	{
		dst = gd->tex_east.addr[ray] + (y * gd->tex_east.line_length
				+ 0 * (gd->tex_east.bits_per_pixel / 8));
	}
	if (card == WE)
	{
		dst = gd->tex_west.addr[ray] + (y * gd->tex_west.line_length
				+ 0 * (gd->tex_west.bits_per_pixel / 8));
	}
	return (*(unsigned int *)dst);
}
