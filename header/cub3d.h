/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:47:44 by jrenault          #+#    #+#             */
/*   Updated: 2024/01/26 22:41:55 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/libft.h"

enum e_colors
{
	F = 0,
	C = 1
};

enum e_textures
{
	NO = 0,
	SO = 1,
	WE = 2,
	EA = 3
};

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		nb_lines;
	int		fd;
	int		*check_colors;
	int		*textures;
	int		*floor_color;
	int		*sky_color;
	char	*map_name;
	char	**map;
	char	**map_textures;
	int		max_x;
	int		max_y;
	int		beginning_map;
}			t_data;

int		main(int argc, char **argv);
int		init_param(t_data *param);

//parsing
int		is_name_correct(t_data *param);
int		map_parsing(t_data *param);
int		is_line_map(char *buf);
int		check_infos(t_data *param);
int		find_infos(t_data *param);
int		fill_textures_colors(char *buf, t_data *param);
int		check_error(t_data *param);
int		fill_line_map(char *buf, t_data *param, int i);

//exec
int		close_win(t_data *param);
int		deal_key(int key, t_data *param);
int		show_minimap(t_data *param);

//free
int		free_all_param(t_data *param);
//int		free_init(t_data *param);

//utils
void	print_double_char(char **str);
int		ft_strlen_space(char *str);
int		is_space_or_newline(char *buf);
char	*go_to_map(t_data *param);

#endif