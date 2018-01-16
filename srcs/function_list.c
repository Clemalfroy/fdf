/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_push_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 16:34:22 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 12:37:08 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_list_push_back(t_pos **begin_list, int x, int y, int z)
{
	t_pos	*elem;

	elem = *begin_list;
	if (begin_list && *begin_list)
	{
		elem = *begin_list;
		while (elem->next)
		{
			elem = elem->next;
		}
		elem->next = ft_create_elem(x, y, z);
	}
	else
		*begin_list = ft_create_elem(x, y, z);
}

t_pos		*ft_create_elem(int x, int y, int z)
{
	t_pos *element;

	element = malloc(sizeof(*element));
	element->x = x;
	element->y = y;
	element->z = z;
	element->next = NULL;
	return (element);
}

void		ft_list_foreach(t_env *begin_list, void (*f)(t_env *, t_pos *,
			t_pos *, int k), t_pos *pos_list)
{
	t_pos *pos;

	pos = pos_list;
	while (pos->next)
	{
		(*f)(begin_list, pos, pos->next, 0);
		pos = pos->next;
	}
}

void		ft_list_clear(t_pos **begin_list)
{
	t_pos *temp;

	if (!begin_list || !*begin_list)
		return ;
	while (*begin_list)
	{
		temp = *begin_list;
		*begin_list = (*begin_list)->next;
		free(temp);
	}
	*begin_list = NULL;
}
