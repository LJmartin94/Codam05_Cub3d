/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/10 15:08:03 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_initraydata(t_raydata *r, t_mapinfo *m);

int		ft_castray(t_data *d)
{
	int x;

	x = 0;
	ft_initraydata(&(d->r), d->m);
	while (x <= d->m->resx)
	{
		d->r.wixel = 2 * x / (double)d->m->resx - 1;
		d->r.rxdir = d->r.pxdir + d->r.xplane * d->r.wixel;
		d->r.rydir = d->r.pydir + d->r.yplane * d->r.wixel;
		d->r.rxpos = (int)d->r.pxpos;
		d->r.rypos = (int)d->r.pypos;
		d->r.wedelta = sqrt(1 + (d->r.rydir * d->r.rydir) / \
		(d->r.rxdir * d->r.rxdir)); //this is sometimes inf
		d->r.nsdelta = sqrt(1 + (d->r.rxdir * d->r.rxdir) / \
		(d->r.rydir * d->r.rydir)); //this is sometimes inf
		x++;
	}
	return (0);
}

int		ft_initraydata(t_raydata *r, t_mapinfo *m)
{
	double fov;

	fov = 0.66;
	r->pxpos = (double)m->posx;
	r->pypos = (double)m->posy;
	r->pxdir = (m->facing == 'E') ? 1 : 0;
	r->pydir = (m->facing == 'S') ? 1 : 0;
	r->pxdir = (m->facing == 'W') ? -1 : r->pxdir;
	r->pydir = (m->facing == 'N') ? -1 : r->pydir;
	r->xplane = (r->pxdir == 1) ? fov : 0;
	r->yplane = (r->pydir == 1) ? (-1 * fov) : 0;
	r->xplane = (r->pxdir == -1) ? (-1 * fov) : r->xplane;
	r->yplane = (r->pydir == -1) ? fov : r->yplane;
	r->wixel = 0;
	r->rxdir = 0;
	r->rydir = 0;
	r->rxpos = 0;
	r->rypos = 0;
	r->nsside = 0;
	r->weside = 0;
	r->nsdelta = 0;
	r->wedelta = 0;
	r->raylen = 0;
	return (0);
}
