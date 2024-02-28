/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:54:28 by tmalidi           #+#    #+#             */
/*   Updated: 2024/02/27 21:28:58 by tmalidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void    front_back_move(int key, t_data *gd)
{
   if (key == 113)
    {
        gd->pos_y -= (gd->x2*sin(120 * M_PI / 180.0) + gd->y2*cos(120 * M_PI / 180.0)) / 100;
        gd->pos_x -= (gd->x2*cos(120 * M_PI / 180.0) - gd->y2*sin(120 * M_PI / 180.0)) / 100;
    }
    else if (key == 100)
    {
        gd->pos_y += (gd->x2*sin(120 * M_PI / 180.0) + gd->y2*cos(120 * M_PI / 180.0)) / 100;
        gd->pos_x += (gd->x2*cos(120 * M_PI / 180.0) - gd->y2*sin(120 * M_PI / 180.0)) / 100; 
    } 
}

void    rotate_view(int key, t_data *gd)
{
    if (key == 65361)
    {
        gd->x2 = gd->x2*cos(gd->angle) + gd->y2*sin(gd->angle);
        gd->y2 = -gd->x2*sin(gd->angle) + gd->y2*cos(gd->angle);
    }
    else if (key == 65363)
    {
        gd->x2 = gd->x2*cos(gd->angle) - gd->y2*sin(gd->angle);
        gd->y2 = gd->x2*sin(gd->angle) + gd->y2*cos(gd->angle); 
    }
}

int	ft_key(int key, t_data *gd)
{
	if (key == 65307)
		exit_game(gd);
    if (key == 119 || key == 65362)
    {
        gd->pos_y += (gd->x2*sin(gd->copy_angle) + gd->y2*cos(gd->copy_angle)) / 100;
        gd->pos_x += (gd->x2*cos(gd->copy_angle) - gd->y2*sin(gd->copy_angle)) / 100;
    }
    else if (key == 115 || key == 65364)
    {
        gd->pos_y -= (gd->x2*sin(gd->copy_angle) + gd->y2*cos(gd->copy_angle)) / 100;
        gd->pos_x -= (gd->x2*cos(gd->copy_angle) - gd->y2*sin(gd->copy_angle)) / 100;
    }
    else if (key == 65363 || key == 65361)
        rotate_view(key,gd);
    else if (key == 113 || key == 100)
        front_back_move(key, gd);
    mlx_clear_window(gd->mlx,gd->win);
    //making_map(gd);
    draw_floor(gd);
    draw_player_view(gd);
    mlx_put_image_to_window(gd->mlx,gd->win2,gd->gi,0,0);
    //collision(gd,gd->pos_x,gd->pos_y);
	return (0);
}
