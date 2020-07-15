/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_quit.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 13:38:48 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/15 10:52:09 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_quit(int ret, t_mapinfo *m)
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
	exit(ret);
}
