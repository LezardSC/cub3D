/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:43 by jrenault          #+#    #+#             */
/*   Updated: 2024/01/30 13:05:25 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

static int	check_argc(int argc)
{
	if (argc < 2)
		return (ft_printf("Error\nNo map given to the program.\n"),
			1);
	if (argc > 2)
		return (ft_printf("Error\nToo many arguments.\n"), 1);
	return (0);
}

static int	parsing_and_error(t_data *param, char *name)
{
	if (init_param(param) == 1)
		return (1);
	param->map_name = ft_strdup(name);
	if (!param->map_name)
		return (1);
	if (is_name_correct(param))
	{
		ft_printf("Error\nThe map is not a valid '.cub'.\n");
		return (1);
	}
	if (map_parsing(param))
		return (1);
	if (check_error(param) == 1)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	param;

	if (check_argc(argc))
		return (1);
	if (parsing_and_error(&param, argv[1]))
	{
		free_all_param(&param);
		close(param.fd);
		return (1);
	}
	param.mlx = mlx_init();
	if (!param.mlx)
		return (free_all_param(&param),
			mlx_destroy_display(param.mlx), free(param.mlx), 1);
	param.win = mlx_new_window(param.mlx,
			1920, 1080, "cub3d");
	if (init_pixels(&param) == 1)
		return (free_all_param(&param),
			mlx_destroy_display(param.mlx), free(param.mlx), 1);
	if (init_player(&param) == 1)
		return (free_all_param(&param),
			mlx_destroy_display(param.mlx), free(param.mlx), 1);
	param.pixel.img = mlx_new_image(param.mlx,
			MINIMAP_WIDTH, MINIMAP_HEIGHT);
	param.pixel.addr = mlx_get_data_addr(param.pixel.img, &param.pixel.bits_per_pixel,
			&param.pixel.line_length, &param.pixel.endian);
	if (show_minimap(&param) == 1)
		return (free_all_param(&param), mlx_destroy_display(param.mlx),
			free(param.mlx), 1);
	mlx_hook(param.win, 02, 1L << 0, deal_key, &param);
	mlx_hook(param.win, 17, 0, close_win, &param);
	mlx_key_hook(param.win, key_release, &param);
	mlx_loop_hook(param.mlx, move_player, &param);
	mlx_loop(param.mlx);
	free_all_param(&param);
	mlx_clear_window(param.mlx, param.win);
	mlx_destroy_image(param.mlx, param.pixel.img);
	mlx_destroy_display(param.mlx);
	return (free(param.mlx), close(param.fd), 0);
}
