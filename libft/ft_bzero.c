/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgabet <lgabet@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:13:13 by lgabet            #+#    #+#             */
/*   Updated: 2023/09/21 11:13:15 by lgabet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *memo, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)memo)[i] = '\0';
		i++;
	}
	return (memo);
}