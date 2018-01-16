/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 10:37:26 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 18:45:08 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "../libft/includes/libft.h"
# include "utility.h"

# ifndef FT_PAGE_SIZE
#  if defined PAGE_SIZE && PAGE_SIZE <= 4096
#   define FT_PAGE_SIZE PAGE_SIZE
#  elif defined PAGESIZE && PAGESIZE <= 4096
#   define FT_PAGE_SIZE PAGESIZE
#  else
#   define FT_PAGE_SIZE 4096
#  endif
# endif

# define WIN_X 1450
# define WIN_Y 725
# define IMG_X 1200
# define IMG_Y 725

typedef struct		s_draw
{
	int				dx;
	int				dy;
	int				i;
	int				xinc;
	int				yinc;
	int				cumul;
	int				x;
	int				y;
}					t_draw;

typedef struct		s_pos
{
	int				x;
	int				y;
	int				z;
	struct s_pos	*next;
}					t_pos;

typedef struct		s_env
{
	void			*mlx;
	void			*win;

	void			*img;
	char			*i_img;
	int				bpp;
	int				size_l;
	int				endian;

	t_pos			*pos;

	int				nb;
	int				nb_line;

	int				maxy;
	int				maxh;

	int				ampli;
	int				color;
	int				zoom;
	double			rotat;
	int				start_x;
	int				start_y;
	int				move;
}					t_env;

/*
 ** Fonction de Parsing.
*/

void				error(int fd);
void				read_file(int fd, t_env *env);
int					open_file(char *file);
int					ft_str_is_numeric(char *str);

/*
 ** Fonction de gestion d'Event.
*/

int					mouse_motion(int x, int y, t_env *env);
int					mouse_hook(int button, int x, int y, t_env *env);
int					ft_keypress(int key, t_env *env);
int					ft_keyrelease(int key, t_env *env);

/*
 ** Fonction de Draw.
*/

void				helper(void *mlx, void *win);
int					color(int z1, int z2, int color);
void				refresh(t_env *env);
void				draw(t_env *env, t_pos *pos);
void				draw_line(t_env *env, t_pos *one, t_pos *other, int k);
void				ft_put_pixel(t_env *env, int x, int y, int color);

/*
 ** Fonction de Liste.
*/

void				ft_list_push_back(t_pos **begin_list, int x, int y, int z);
void				ft_list_foreach(t_env *begin_list, void (*f)(t_env *, t_pos
			*, t_pos *, int k), t_pos *pos_list);
t_pos				*ft_create_elem(int x, int y, int z);
void				ft_list_clear(t_pos **begin_list);

#endif
