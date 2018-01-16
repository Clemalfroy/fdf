/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/09 09:53:51 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 18:46:59 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		error(int i)
{
	ft_putstr("Invalid map or wrong argument, usage : fdf [valid_map]\n");
	exit(i);
}

int			color(int z1, int z2, int color)
{
	if (z1 - z2 == 0)
	{
		if (z1 != 0)
			return (z1 * color);
		else
			return (color);
	}
	return (ft_abs(z1 - z2) * color);
}

int			ft_str_is_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '+' || str[i] == '-')
		{
			if (str[i + 1] < 48 || str[i] > 57)
				return (0);
			i++;
		}
		if (str[i] && (str[i] < 48 || str[i] > 57) && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}
