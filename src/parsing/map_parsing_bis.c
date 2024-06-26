/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenault <jrenault@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 15:17:15 by jrenault          #+#    #+#             */
/*   Updated: 2024/01/31 16:59:34 by jrenault         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	is_line_map(char *buf)
{
	int	i;

	i = 1;
	if (buf[0] == '1' || buf[0] == '0' || (buf[0] == 'N' && buf[1] != 'O')
		|| (buf[0] == 'S' && buf[1] != 'O') || (buf[0] == 'W' && buf[1] != 'E')
		|| (buf[0] == 'E' && buf[1] != 'A'))
		return (1);
	else if (buf[0] == ' ')
	{
		while (buf[i])
		{
			if (buf[i] == '1' || buf[i] == '0' || buf[i] == 'N'
				|| buf[i] == 'S' || buf[i] == 'W' || buf[i] == 'E')
				return (1);
			i++;
		}
	}
	return (0);
}

int	is_name_correct(t_data *param)
{
	int	size;

	size = ft_strlen(param->map_name);
	if (size >= 5 && param->map_name[size - 1] == 'b'
		&& param->map_name[size - 2] == 'u' && param->map_name[size - 3] == 'c'
		&& param->map_name[size - 4] == '.')
		return (0);
	return (1);
}
