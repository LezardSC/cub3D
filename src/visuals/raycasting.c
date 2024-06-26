/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:13:58 by tmalidi           #+#    #+#             */
/*   Updated: 2024/04/08 11:17:56 by tmalidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

float	calc_dist(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	init_line_data(t_line_data *data, int x2, int y2, t_data *gd)
{
	data->dx = abs((int)x2 - (int)gd->pos_x);
	data->dy = abs((int)y2 - (int)gd->pos_y);
	data->x1 = gd->pos_x;
	data->y1 = gd->pos_y;
	if (gd->pos_x < x2)
		data->sx = 1;
	else
		data->sx = -1;
	if (gd->pos_y < y2)
		data->sy = 1;
	else
		data->sy = -1;
	data->err = data->dx - data->dy;
}

void	ray_value(t_ray_data *ray, t_line_data *data, int ray_id)
{
	ray->x = data->x1;
	ray->y = data->y1;
	ray->id = ray_id;
	ray->dist = -1;
}

t_ray_data	draw_line(t_data *gd, int x2, int y2, int ray_id)
{
	t_line_data	data;
	t_ray_data	ray;

	init_line_data(&data, x2, y2, gd);
	while (1)
	{
		if ((data.x1 == x2 && data.y1 == y2)
			|| !collision(gd, data.x1, data.y1))
			break ;
		data.e2 = 2 * data.err;
		if (data.e2 > -data.dy)
		{
			data.err -= data.dy;
			data.x1 += data.sx;
		}
		if (data.e2 < data.dx)
		{
			data.err += data.dx;
			data.y1 += data.sy;
		}
	}
	ray_value(&ray, &data, ray_id);
	if (data.x1 != x2 || data.y1 != y2)
		ray.dist = calc_dist(gd->pos_x, gd->pos_y, data.x1, data.y1);
	return (ray);
}
