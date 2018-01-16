/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:27:07 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 18:15:32 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		refresh(t_env *e)
{
	ft_memset(e->i_img, 0, (WIN_Y * e->size_l) + (e->maxh * (e->bpp / 8)));
	draw(e, e->pos);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void		ft_put_pixel(t_env *env, int x, int y, int color)
{
	if (y >= IMG_Y || x >= IMG_X || x < 0 || y < 0)
		return ;
	*(int *)&env->i_img[(y * env->size_l) + (x * (env->bpp / 8))] = color;
}

void		draw(t_env *env, t_pos *pos)
{
	t_pos	*test;
	t_pos	*cpy;
	int		i;

	test = pos;
	cpy = pos;
	ft_list_foreach(env, draw_line, pos);
	cpy = cpy->next;
	i = 0;
	while (cpy->next && ++i != env->nb)
		cpy = cpy->next;
	while (cpy)
	{
		draw_line(env, test, cpy, 1);
		test = test->next;
		cpy = cpy->next;
	}
}

void		fill_draw_struct(t_pos *one, t_pos *other, t_draw *p, t_env *env)
{
	p->x = env->start_x + (one->x - one->y) * env->zoom;
	p->y = env->start_y + ((one->y + one->x) * env->zoom) - (one->z *
			env->ampli);
	p->dx = (env->start_x + (other->x - other->y) * env->zoom) - p->x;
	p->dy = (env->start_y + ((other->y + other->x) * env->zoom) - (other->z *
				env->ampli)) - p->y;
	p->xinc = (p->dx > 0) ? 1 : -1;
	p->yinc = (p->dy > 0) ? 1 : -1;
	p->dx = p->dx < 0 ? p->dx * -1 : p->dx;
	p->dy = p->dy < 0 ? p->dy * -1 : p->dy;
}

void		draw_line(t_env *env, t_pos *one, t_pos *other, int k)
{
	t_draw p;

	fill_draw_struct(one, other, &p, env);
	if ((p.i = 0) <= p.dx && p.dx > p.dy)
	{
		p.cumul = p.dx / 2;
		while (++p.i <= p.dx && (p.cumul += p.dy) >= 0 && (p.y += p.cumul >=
					p.dx && (p.cumul -= p.dx) >= 0 ? p.yinc : 0) >= 0)
			if ((p.x += p.xinc) >= 0 && (one->x < other->x || k == 1))
				ft_put_pixel(env, p.x, p.y / env->rotat, color(one->z, other->z,
							env->color));
	}
	else
	{
		p.cumul = p.dy / 2;
		while (++p.i <= p.dy && (p.cumul += p.dx) >= 0 && (p.x += p.cumul >=
					p.dy && (p.cumul -= p.dy) >= 0 ? p.xinc : 0) >= 0)
			if ((p.y += p.yinc) >= 0 && (one->x < other->x || k == 1))
				ft_put_pixel(env, p.x, p.y / env->rotat, color(one->z, other->z,
							env->color));
	}
}
