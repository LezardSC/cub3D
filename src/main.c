/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalidi <tmalidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:02:43 by jrenault          #+#    #+#             */
/*   Updated: 2024/02/27 21:15:48 by tmalidi          ###   ########.fr       */
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

//This function will check error and parse.
//I don't think you don't need to touch it.

static int	parsing_and_error(t_data *param, char *name)
{
	if (init_param(param) == 1)
		return (ft_printf("Error\nError in initialization\n"), 1);
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

//end the program and free everything

static void	end_program(t_data *param)
{
	free_all_param(param);
	mlx_clear_window(param->mlx, param->win);
	mlx_destroy_image(param->mlx, param->pixel.img);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	close(param->fd);
}

//Will create the image of the minimap.
//That's where you need to start include your code.
//The minimap has to be displayed after the map so...

static int	display_map(t_data *param)
{
	param->pixel.img = mlx_new_image(param->mlx,
			MINIMAP_WIDTH, MINIMAP_HEIGHT);
	param->pixel.addr = mlx_get_data_addr(param->pixel.img,
			&param->pixel.bits_per_pixel,
			&param->pixel.line_length, &param->pixel.endian);
	if (show_minimap(param) == 1)
		return (free_all_param(param), mlx_destroy_display(param->mlx),
			free(param->mlx), 1);
	return (0);
}

/*
-bzero secure the struct.
-check_argc check if there is only one arg, which is the map.
-parsing and error will parse the map to be sure it's an existing and correct map.
-we init mlx and window.
-init_pixels will init the pixel size of the minimap. We will have to adjust that to work with the real map too.
-display_map will show the minimap on the screen. We will have to adjust that to work with the real map too.
-the mlx hook deal with keys, close the windows, move the player dynamically, etc. We will have to adjust the real map moves to adapt.
-key release and move player allow the player to move smoothly.
*/

int	main(int argc, char **argv)
{
	t_data	param;

	ft_bzero(&param, sizeof(t_data));
	//ft_put_3dview(&param);
	if (check_argc(argc))
		return (1);
	if (parsing_and_error(&param, argv[1]))
		return (free_all_param(&param), close(param.fd), 1);
	param.mlx = mlx_init();
	if (!param.mlx)
		return (free_all_param(&param),
			mlx_destroy_display(param.mlx), free(param.mlx), 1);
	param.win = mlx_new_window(param.mlx,
			1920, 1080, "cub3d");
	if (init_pixels(&param) == 1)
		return (free_all_param(&param),
			mlx_destroy_display(param.mlx), free(param.mlx), 1);
	ft_put_windows(&param);
	if (display_map(&param) == 1)
		return (1);
	mlx_hook(param.win, 02, 1L << 0, deal_key, &param);
	mlx_hook(param.win, 17, 0, close_win, &param);
	mlx_key_hook(param.win, key_release, &param);
	mlx_loop_hook(param.mlx, move_player, &param);
	mlx_loop(param.mlx);
	return (end_program(&param), 0);
}
