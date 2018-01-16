/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 10:12:12 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/10 18:47:45 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#define S str[fd]

int				get_next_line(const int fd, char **line)
{
	int			rd;
	char		buf[FT_PAGE_SIZE + 1];
	static char *str[1];
	char		*cpy;

	if (!line || fd < 0 || !(S = S ? S : ft_strnew(1)))
		return (-1);
	while (!ft_strchr(S, '\n') && (rd = read(fd, buf, FT_PAGE_SIZE)) != 0)
	{
		if (rd == ((buf[rd] = '\0') - 1))
			return (-1);
		cpy = ft_strjoin(S, buf);
		free(S);
		S = cpy;
	}
	*line = (ft_strchr(S, '\n') ? ft_strsub(S, 0,
				ft_strchr(S, '\n') - S) : ft_strdup(S));
	if (ft_strchr(cpy = S, '\n'))
	{
		S = ft_strsub(S, ft_strchr(S, '\n') - S + 1, ft_strlen(S));
		free(cpy);
	}
	else
		ft_strdel(&S);
	return (!S && ft_strlen(*line) == 0 ? 0 : 1);
}

int				open_file(char *file)
{
	int fd;

	fd = open(file, O_DIRECTORY);
	if (fd > 0)
		return (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

t_pos			*fill_lst(t_pos *pos, char *line, int y, t_env *env)
{
	char	**tab;
	int		x;
	int		z;

	x = -1;
	if (ft_str_is_numeric(line) == 0)
		return (NULL);
	tab = ft_strsplit(line, ' ');
	while (tab[++x])
	{
		z = ft_atoi(tab[x]);
		ft_list_push_back(&pos, x, y, z);
		free(tab[x]);
	}
	if (y != 0 && x != env->nb)
		return (NULL);
	free(tab);
	free(line);
	env->nb = x;
	return (pos);
}

void			read_file(int fd, t_env *env)
{
	int			y;
	char		*line;
	t_pos		*pos;

	pos = NULL;
	y = -1;
	while (get_next_line(fd, &line) > 0)
	{
		pos = fill_lst(pos, line, ++y, env);
		env->nb_line = y;
		if (pos == NULL)
			error(1);
	}
	free(line);
	close(fd);
	env->pos = pos;
}
