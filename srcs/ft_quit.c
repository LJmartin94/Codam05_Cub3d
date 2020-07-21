/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_quit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 13:38:48 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/21 21:48:12 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	xt_quit(int ret, t_mapinfo *m)
{
	if (m->fd != -1)
		close(m->fd);
	if (m->northtex != NULL)
		free(m->northtex);
	if (m->southtex != NULL)
		free(m->southtex);
	if (m->westtex != NULL)
		free(m->westtex);
	if (m->easttex != NULL)
		free(m->easttex);
	if (m->spritetex != NULL)
		free(m->spritetex);
	if (m->map != NULL)
	{
		m->x = 0;
		while (m->x < m->ydim)
		{
			free(m->map[m->x]);
			m->x++;
		}
		free(m->map);
		m->map = NULL;
	}
	ft_clearcopy(0, m->copy, m);
	exit(ret);
}

int		ft_clearcopy(int error, t_mapinfo *c, t_mapinfo *org)
{
	int lines;

	if (org->copy == NULL)
		return (0);
	if (c->map != NULL)
	{
		lines = 0;
		while (lines < c->ydim)
		{
			free(c->map[lines]);
			lines++;
		}
		free(c->map);
		c->map = NULL;
	}
	free(org->copy);
	org->copy = NULL;
	if (error == 1)
		xt_mallocerror(org);
	return (0);
}
