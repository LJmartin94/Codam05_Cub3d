/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_constructors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/19 14:39:09 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/08 19:19:49 by limartin      ########   odam.nl         */
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
	mapinfo->zbuf = NULL;
	mapinfo->sprites = NULL;
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
	m->zbuf = (double *)malloc(sizeof(double) * m->resx);
	m->sprites = (t_sprite*)malloc(sizeof(t_sprite) * (m->spriteno));
	if (m->zbuf == NULL || m->sprites == NULL)
		xt_mallocerror(m);
	return (0);
}

int			ft_getmovin(t_data *d)
{
	unsigned long	resprod;

	resprod = d->m->resx * d->m->resy;
	d->md.movspd = 0.05 * (resprod / (1280 * 720));
	d->md.movspd = (d->md.movspd < 0.05) ? 0.05 : d->md.movspd;
	d->md.movspd = (d->md.movspd > 0.2) ? 0.2 : d->md.movspd;
	d->md.direct = d->md.movspd;
	d->md.strafe = (sqrt(pow(d->md.movspd, 2) + pow(d->md.movspd, 2))) / 2;
	d->md.rotspd = 0.05;
	d->md.v = 0;
	d->md.h = 0;
	d->md.rotating = 0;
	d->md.newpx = d->r.pxpos;
	d->md.newpy = d->r.pypos;
	return (0);
}

int			ft_getteximgs(t_data *d)
{
	d->tex.north = mlx_xpm_file_to_image(d->mlx, d->m->northtex, \
	&(d->tex.ntex.width), &(d->tex.ntex.height));
	d->tex.south = mlx_xpm_file_to_image(d->mlx, d->m->southtex, \
	&(d->tex.stex.width), &(d->tex.stex.height));
	d->tex.west = mlx_xpm_file_to_image(d->mlx, d->m->westtex, \
	&(d->tex.wtex.width), &(d->tex.wtex.height));
	d->tex.east = mlx_xpm_file_to_image(d->mlx, d->m->easttex, \
	&(d->tex.etex.width), &(d->tex.etex.height));
	d->tex.sprite = mlx_xpm_file_to_image(d->mlx, d->m->spritetex, \
	&(d->tex.sptex.width), &(d->tex.sptex.height));
	if (d->tex.north == NULL || d->tex.south == NULL || \
	d->tex.west == NULL || d->tex.east == NULL || d->tex.sprite == NULL)
		xt_mlxerror(d->m);
	d->tex.ntex.addr = mlx_get_data_addr(d->tex.north, \
	&d->tex.ntex.bits_per_pixel, &d->tex.ntex.line_bytes, &d->tex.ntex.endian);
	d->tex.stex.addr = mlx_get_data_addr(d->tex.south, \
	&d->tex.stex.bits_per_pixel, &d->tex.stex.line_bytes, &d->tex.stex.endian);
	d->tex.wtex.addr = mlx_get_data_addr(d->tex.west, \
	&d->tex.wtex.bits_per_pixel, &d->tex.wtex.line_bytes, &d->tex.wtex.endian);
	d->tex.etex.addr = mlx_get_data_addr(d->tex.east, \
	&d->tex.etex.bits_per_pixel, &d->tex.etex.line_bytes, &d->tex.etex.endian);
	d->tex.sptex.addr = mlx_get_data_addr(d->tex.sprite, \
	&d->tex.sptex.bits_per_pixel, &d->tex.sptex.line_bytes, \
	&d->tex.sptex.endian);
	return (0);
}
