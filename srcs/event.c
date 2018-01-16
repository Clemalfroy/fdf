/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:09:33 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 18:30:16 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	helper(void *mlx, void *win)
{
	mlx_string_put(mlx, win, IMG_X + 10, 20, 0x0FFFFFF, "Fleche: move");
	mlx_string_put(mlx, win, IMG_X + 10, 40, 0x0FFFFFF, "C: Color");
	mlx_string_put(mlx, win, IMG_X + 10, 60, 0x0FFFFFF, "X: Ex color");
	mlx_string_put(mlx, win, IMG_X + 10, 80, 0x0FFFFFF, "U: Increase height");
	mlx_string_put(mlx, win, IMG_X + 10, 100, 0x0FFFFFF, "D: Decrease height");
	mlx_string_put(mlx, win, IMG_X + 10, 120, 0x0FFFFFF, "Z: Large vision");
	mlx_string_put(mlx, win, IMG_X + 10, 140, 0x0FFFFFF, "A: Flattened vision");
	mlx_string_put(mlx, win, IMG_X + 10, 160, 0x0FFFFFF, "Movemouse: Move map");
	mlx_string_put(mlx, win, IMG_X + 10, 180, 0x0FFFFFF, "Button1: Stop movem"
			"ent");
	mlx_string_put(mlx, win, IMG_X + 10, 200, 0x0FFFFFF, "+ / - : Zoom");
	mlx_string_put(mlx, win, IMG_X + 10, 220, 0x0FFFFFF, "Mollette: Zoom");
}

int		ft_keyrelease(int key, t_env *env)
{
	if (key == KEY_ESC)
	{
		mlx_destroy_image(env->mlx, env->img);
		mlx_destroy_window(env->mlx, env->win);
		exit(1);
	}
	return (0);
}

int		ft_keypress(int key, t_env *env)
{
	if (key == KEY_PLUS || key == KEY_MINUS)
		env->zoom += key == KEY_PLUS || env->zoom <= 2 ? 2 : -2;
	else if (key == KEY_DOWN)
		env->start_y -= 0.3 * env->nb;
	else if (key == KEY_UP)
		env->start_y += 0.3 * env->nb;
	else if (key == KEY_LEFT)
		env->start_x += 0.3 * env->nb;
	else if (key == KEY_RIGHT)
		env->start_x -= 0.3 * env->nb;
	else if (key == KEY_R)
		env->zoom = WIN_Y / env->nb;
	else if (key == KEY_C || key == KEY_X)
		env->color += key == KEY_C ? 5000 : -5000;
	else if (key == KEY_U || key == KEY_D)
		env->ampli += key == KEY_U ? 1 : -1;
	else if (key == KEY_Z || key == KEY_A)
		env->rotat += key == KEY_Z ? 0.1 : -0.1;
	refresh(env);
	return (0);
}

int		mouse_motion(int x, int y, t_env *env)
{
	if (env->move)
	{
		env->start_y = y - (env->nb * env->zoom) / 2;
		env->start_x = x - (env->nb_line * env->zoom) / 2;
	}
	refresh(env);
	return (0);
}

int		mouse_hook(int button, int x, int y, t_env *env)
{
	(void)x;
	(void)y;
	if (button == 5 || button == 4)
		env->zoom += button == 5 || env->zoom <= 2 ? 2 : -2;
	if (button == 1)
		env->move = env->move == 1 ? 0 : 1;
	refresh(env);
	return (0);
}
