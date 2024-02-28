/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 19:13:58 by tmalidi           #+#    #+#             */
/*   Updated: 2024/02/27 21:29:08 by tmalidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

float calculerDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float other_draw_line(t_data *gd, int x1, int y1, int x2, int y2, int color)
{
    (void)color;
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;
    while (1)
    {
        put_pixel_to_image(gd,x1,y1,color);
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    if (x1 != x2 || y1 != y2)
    {
        printf("distance == %f\n", calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
        return (calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
    }
    return (-1);
        //draw_vertical_line(gd,calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
}

float draw_line(t_data *gd, int x1, int y1, int x2, int y2, int color)
{
    (void)color;
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;
    while (1)
    {
        //mlx_pixel_put(gd->mlx, gd->win, x1, y1, color);
        if ((x1 == x2 && y1 == y2) || !collision(gd,x1,y1))
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    if (x1 != x2 || y1 != y2)
    {
        printf("distance == %f\n", calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
        return (calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
    }
    return (-1);
}

float draw_line_for_wall(t_data *gd, int x1, int y1, int x2, int y2, int color)
{
    (void)color;
    
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx, sy;

    if (x1 < x2)
        sx = 1;
    else
        sx = -1;

    if (y1 < y2)
        sy = 1;
    else
        sy = -1;

    int err = dx - dy;
    while (1)
    {
        mlx_pixel_put(gd->mlx, gd->win, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
    if (x1 != x2 || y1 != y2)
    {
        printf("distance == %f\n", calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
        return (calculerDistance(gd->pos_x,gd->pos_y,x1,y1));
    }
    return (-1);
}