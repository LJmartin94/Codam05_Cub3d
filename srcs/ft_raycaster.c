/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/07 20:24:05 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_initraydata(t_raydata *r, t_mapinfo *m);

int		ft_castray(t_data *d)
{
	ft_initraydata(&(d->r), d->m);
	printf("Xpos: %f\n", d->r.xpos);
	printf("Ypos: %f\n", d->r.ypos);
	printf("Xdir: %f\n", d->r.xdir);
	printf("Ydir: %f\n", d->r.ydir);

	return (0);
}

int		ft_initraydata(t_raydata *r, t_mapinfo *m)
{
	r->xpos = (double)m->posx;
	r->ypos = (double)m->posy;
	r->xdir = (m->facing == 'E') ? 1 : 0;
	r->ydir = (m->facing == 'S') ? 1 : 0;
	r->xdir = (m->facing == 'W') ? -1 : r->xdir;
	r->ydir = (m->facing == 'N') ? -1 : r->ydir;
	r->xplane = (r->xdir == 1) ? 0.66 : 0;
	r->yplane = (r->ydir == 1) ? -0.66 : 0;
	r->xplane = (r->xdir == -1) ? -0.66 : r->xplane;
	r->yplane = (r->ydir == -1) ? 0.66 : r->yplane;
	return (0);
}
