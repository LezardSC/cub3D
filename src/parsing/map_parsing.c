/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:47:26 by jrenault          #+#    #+#             */
/*   Updated: 2024/01/26 03:15:09 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

static int	allocate_map(t_data *param)
{
	int		i;

	i = 0;
	param->map = malloc(sizeof(char *) * (param->max_y + 2));
	if (!param->map)
		return (ft_printf("Error\nMalloc map error.\n"), 1);
	while (i <= param->max_y)
	{
		param->map[i] = malloc(sizeof(char) * (param->max_x + 2));
		if (!param->map[i])
			return (ft_printf("Error\nMalloc map error."), 1);
		i++;
	}
	param->map[i] = NULL;
	return (0);
}

int	fill_line_map(char *buf, t_data *param, int i)
{
	int	j;

	j = 0;
	while (buf[j] && buf[j] != '\n')
	{
		param->map[i][j] = buf[j];
		j++;
	}
	while (j <= param->max_x)
	{
		param->map[i][j] = ' ';
		j++;
	}
	param->map[i][j] = '\0';
	return (0);
}

static int	fill_map(t_data *param)
{
	int		i;
	char	*buf;

	i = 0;
	close(param->fd);
	param->fd = open(param->map_name, O_RDONLY);
	if (param->fd == -1)
		return (ft_printf("Error\nCouldn't open the map.\n"), 1);
	buf = go_to_map(param);
	if (!buf)
		return (ft_printf("Error\nInvalid map.\n"), 1);
	while (buf)
	{
		if (fill_line_map(buf, param, i) == 1)
			return (ft_printf("Error\nInvalid map.\n"), free(buf), 1);
		free(buf);
		buf = get_next_line(param->fd);
		i++;
	}
	free(buf);
	return (0);
}

int	map_parsing(t_data *param)
{
	param->fd = open(param->map_name, O_RDONLY);
	if (param->fd == -1)
		return (ft_printf("Error\nCouldn't open the map.\n"), 1);
	param->nb_lines = 0;
	param->max_x = 0;
	if (find_infos(param) == 1)
		return (1);
	param->max_y = param->nb_lines - param->beginning_map;
	if (allocate_map(param) == 1)
		return (1);
	if (fill_map(param) == 1)
		return (1);
	return (0);
}
