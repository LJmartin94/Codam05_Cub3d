/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 22:17:07 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/15 11:03:05 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_processmap(t_mapinfo *m, char *cub)
{
	ft_getmap(m, cub);
	return (0);
}

int	ft_getmap(t_mapinfo *m, char *cub)
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
	m->map[m->ydim] = NULL; //check how this should be done properly
	return (0);
}
