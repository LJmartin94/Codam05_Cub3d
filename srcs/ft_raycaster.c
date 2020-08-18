/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/18 18:38:06 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_initraydata(t_raydata *r, t_mapinfo *m);

int		ft_ppostobox(t_data *d);

int		ft_findwall(t_data *d);

int		ft_colourwixel(t_data *d, int x);

int		ft_buildwall(t_data *d, int x, int wstart, int wend);

int		ft_raycastdebug(t_data *d, int x)
{
	if (x % 200 == 0 || d->r.wixel == 0 || d->r.wixel == 1 || d->r.wixel == -1)
	{
		printf("\n\n\n\n\n\n\n\n\n\n\n\n");
		printf("int x: 			%d\n", x);
		printf("double pxpos:	%f\n", d->r.pxpos);
		printf("double pypos:	%f\n", d->r.pypos);
		printf("double pxdir:	%f\n", d->r.pxdir);
		printf("double pydir:	%f\n", d->r.pydir);
		printf("double xplane:	%f\n", d->r.xplane);
		printf("double yplane:	%f\n", d->r.yplane);
		printf("double wixel:	%f\n", d->r.wixel);
		printf("double rxdir:	%f\n", d->r.rxdir);
		printf("double rydir:	%f\n", d->r.rydir);
		printf("double rxpos:	%d\n", d->r.rxpos);
		printf("double rypos:	%d\n", d->r.rypos);
		printf("double wedelta:	%f\n", d->r.wedelta);
		printf("double nsdelta:	%f\n", d->r.nsdelta);

		printf("int stepx:		%d\n", d->r.stepx);
		printf("int stepy:		%d\n", d->r.stepy);
		printf("double weside:	%f\n", d->r.weside);
		printf("double nsside:	%f\n", d->r.nsside);
	}
	return (0);
}

int		ft_castray(t_data *d)
{
	int x;

	x = 0;
	ft_initraydata(&(d->r), d->m);
	while (x <= d->m->resx)
	{
		d->r.wixel = -1 + (x / (double)d->m->resx) * 2;
		d->r.rxdir = d->r.pxdir + d->r.xplane * d->r.wixel;
		d->r.rydir = d->r.pydir + d->r.yplane * d->r.wixel;
		d->r.rxpos = (int)d->r.pxpos;
		d->r.rypos = (int)d->r.pypos;
		d->r.wedelta = sqrt(1 + (d->r.rydir * d->r.rydir) / \
		(d->r.rxdir * d->r.rxdir)); //this is sometimes inf
		d->r.nsdelta = sqrt(1 + (d->r.rxdir * d->r.rxdir) / \
		(d->r.rydir * d->r.rydir)); //this is sometimes inf
		ft_ppostobox(d);
		ft_findwall(d);
		ft_colourwixel(d, x);
		//ft_raycastdebug(d, x);
		x++;
	}
	return (0);
}

int		ft_initraydata(t_raydata *r, t_mapinfo *m)
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
	r->yplane = (r->pxdir == -1) ? (-1 * fov) : r->yplane; //making the plane negative might be wrong
	r->xplane = (r->pydir == -1) ? fov : r->xplane;
	return (0);
}

int		ft_ppostobox(t_data *d)
{
	d->r.stepx = 0;
	d->r.stepy = 0;
	d->r.weside = 0; //this is also sometimes infinite, in case rxdir = 0
	d->r.nsside = 0; //this is also sometimes infinite
	if (d->r.rxdir < 0)
	{
		d->r.stepx = -1;
		d->r.weside = (d->r.pxpos - d->r.rxpos) * d->r.wedelta;
	}
	else if (d->r.rxdir >= 0)
	{
		d->r.stepx = 1;
		d->r.weside = (d->r.rxpos + 1 - d->r.pxpos) * d->r.wedelta;
	}
	if (d->r.rydir < 0)
	{
		d->r.stepy = -1;
		d->r.nsside = (d->r.pypos - d->r.rypos) * d->r.nsdelta;
	}
	else if (d->r.rydir >= 0)
	{
		d->r.stepy = 1;
		d->r.nsside = (d->r.rypos + 1 - d->r.pypos) * d->r.nsdelta;
	}
	return (0);
}

int		ft_findwall(t_data *d)
{
	d->r.hit = 0;
	while (d->r.hit == 0)
	{
		if (d->r.weside < d->r.nsside)
		{
			d->r.pole = 0;
			d->r.rxpos = d->r.rxpos + d->r.stepx;
			d->r.weside = d->r.weside + d->r.wedelta;
		}
		else
		{
			d->r.pole = 1;
			d->r.rypos = d->r.rypos + d->r.stepy;
			d->r.nsside = d->r.nsside + d->r.nsdelta;
		}
		d->r.hit = (d->m->map[d->r.rypos][d->r.rxpos] > '0') ? 1 : 0;
	}
	return (0);
}

int		ft_colourwixel(t_data *d, int x)
{
	int		se;
	int		hwall;
	int		wstart;
	int		wend;

	se = ((d->r.pole == 0 && d->r.stepx == -1) || \
	(d->r.pole == 1 && d->r.stepy == -1)) ? 1 : 0;
	d->r.camraylen = (d->r.pole == 0) ? \
	((d->r.rxpos - d->r.pxpos + se) / d->r.rxdir) : \
	((d->r.rypos - d->r.pypos + se) / d->r.rydir);
	hwall = (int)(d->m->resy / d->r.camraylen);
	wstart = d->m->resy / 2 - hwall / 2;
	wstart = (wstart < 0) ? 0 : wstart;
	wend = d->m->resy / 2 + hwall / 2;
	wend = (wend >= d->m->resy) ? d->m->resy - 1 : wend;
	ft_buildwall(d, x, wstart, wend);
	return (x);
}

int		ft_buildwall(t_data *d, int x, int wstart, int wend)
{
	int		y;
	int		colour;
	t_img	*img;

	y = 0;
	colour = (d->m->cb + d->m->cg * 256 + d->m->cr * 256 * 256);
	img = (d->frame % 2 == 1) ? &(d->imga) : &(d->imgb);
	while (y < wstart)
	{
		ft_put_pixel_img(img, x, y, colour);
		y++;
	}
	colour = (d->r.pole == 1) ? 0xCC6600 : 0xA6692C;
	while (y < wend)
	{
		ft_put_pixel_img(img, x, y, colour);
		y++;
	}
	colour = (d->m->fb + d->m->fg * 256 + d->m->fr * 256 * 256);
	while (y < d->m->resy)
	{
		ft_put_pixel_img(img, x, y, colour);
		y++;
	}
	return (0);
}
