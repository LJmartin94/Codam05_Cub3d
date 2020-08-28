/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_constructors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 14:39:09 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/28 20:00:51 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_mapinfo	ft_constructor(t_mapinfo *mapinfo)
{
	mapinfo->fd = -1;
	mapinfo->noerror = 1;
	mapinfo->resx = -1;
	mapinfo->resy = -1;
	mapinfo->northtex = NULL;
	mapinfo->southtex = NULL;
	mapinfo->westtex = NULL;
	mapinfo->easttex = NULL;
	mapinfo->spritetex = NULL;
	mapinfo->spriteno = 0;
	mapinfo->fr = -1;
	mapinfo->fg = -1;
	mapinfo->fb = -1;
	mapinfo->cr = -1;
	mapinfo->cg = -1;
	mapinfo->cb = -1;
	mapinfo->facing = '\0';
	mapinfo->mapstart = 0;
	mapinfo->ydim = 1;
	mapinfo->map = NULL;
	mapinfo->copy = NULL;
	return (*mapinfo);
}

int			ft_initraydata(t_raydata *r, t_mapinfo *m)
{
	double fov;

	fov = 0.66;
	r->pxpos = (double)m->posx + 0.5;
	r->pypos = (double)m->posy + 0.5;
	r->pxdir = (m->facing == 'E') ? 1 : 0;
	r->pydir = (m->facing == 'S') ? 1 : 0;
	r->pxdir = (m->facing == 'W') ? -1 : r->pxdir;
	r->pydir = (m->facing == 'N') ? -1 : r->pydir;
	r->yplane = (r->pxdir == 1) ? fov : 0;
	r->xplane = (r->pydir == 1) ? (-1 * fov) : 0;
	r->yplane = (r->pxdir == -1) ? (-1 * fov) : r->yplane;
	r->xplane = (r->pydir == -1) ? fov : r->xplane;
	m->map[m->posy][m->posx] = '0';
	return (0);
}

int			ft_getmovin(t_data *d)
{
	d->md.movspd = 0.05;
	d->md.rotspd = 0.05;
	d->md.perpmov = 0;
	d->md.parmov = 0;
	d->md.rotating = 0;
	return (0);
}
