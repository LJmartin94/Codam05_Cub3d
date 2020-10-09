/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_quit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 13:38:48 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/09 17:14:39 by lindsay       ########   odam.nl         */
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
		ft_freemap(m);
	if (m->zbuf != NULL)
		free(m->zbuf);
	if (m->sprites != NULL)
		free(m->sprites);
	ft_clearcopy(0, m->copy, m);
	exit(ret);
}

int		ft_freemap(t_mapinfo *m)
{
	m->x = 0;
	while (m->x < m->ydim)
	{
		free(m->map[m->x]);
		m->x++;
	}
	free(m->map);
	m->map = NULL;
	return (0);
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

int	xt_wrerror(t_mapinfo *m)
{
	errno = 9;
	perror("Error\n A file could not be opened, closed or written to as \
	necessary\n");
	xt_quit(1, m);
	return (1);
}
