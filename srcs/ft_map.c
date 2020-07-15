/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 22:17:07 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/15 18:26:27 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_processmap(t_mapinfo *m, char *cub)
{
	t_mapinfo ffm;

	ft_getmap(m, cub);
	ft_scanmap(m);
	if (m->noerror == 0)
		ft_parserror(2, m);
	ft_copymap(m, &ffm);
	return (0);
}

int		ft_getmap(t_mapinfo *m, char *cub)
{
	char	*line;
	int		i;

	close(m->fd);
	m->fd = open(cub, O_RDONLY);
	while (m->mapstart > 0)
	{
		get_next_line(m, &line);
		m->mapstart--;
		free(line);
	}
	m->map = (char **)malloc(sizeof(char *) * (m->ydim + 1));
	if (m->map == 0)
		ft_mallocerror(m);
	i = m->ydim;
	m->ydim = 0;
	while (m->ydim < i)
	{
		get_next_line(m, &(m->map[m->ydim]));
		m->ydim++;
	}
	m->map[m->ydim] = NULL;
	return (0);
}

void	ft_scanmap(t_mapinfo *m)
{
	int i;
	int j;

	m->noerror = (m->ydim < 1) ? 0 : m->noerror;
	i = 0;
	while (m->map[i] != NULL)
	{
		j = 0;
		while (m->map[i][j] != '\0')
		{
			if (m->facing == '\0' && (m->map[i][j] == 'N' || \
		m->map[i][j] == 'S' || m->map[i][j] == 'W' || m->map[i][j] == 'E'))
			{
				m->facing = m->map[i][j];
				m->posy = i;
				m->posx = j;
			}
			else if (m->map[i][j] != ' ' && m->map[i][j] != '0' \
		&& m->map[i][j] != '1' && m->map[i][j] != '2')
				m->noerror = 0;
			j++;
		}
		i++;
	}
}

int		ft_copymap(t_mapinfo *original, t_mapinfo *copy)
{
	copy->map = (char **)malloc(sizeof(char *) * (m->ydim + 1)); //HALF WRITTEN, REVIEW
}