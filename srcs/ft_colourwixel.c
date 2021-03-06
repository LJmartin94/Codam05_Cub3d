/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_colourwixel.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:39:38 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/08 14:08:41 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
	d->m->zbuf[x] = d->r.camraylen;
	hwall = (int)(d->m->resy / d->r.camraylen);
	wstart = d->m->resy / 2 - hwall / 2;
	wstart = (wstart < 0) ? 0 : wstart;
	wend = d->m->resy / 2 + hwall / 2;
	wend = (wend >= d->m->resy) ? d->m->resy : wend;
	d->thisframe = (d->frame % 2 == 1) ? &(d->imga) : &(d->imgb);
	ft_buildwall(d, x, wstart, wend);
	return (x);
}

int		ft_buildwall(t_data *d, int x, int wstart, int wend)
{
	int		y;
	int		colour;

	y = 0;
	colour = (d->m->cb + d->m->cg * 256 + d->m->cr * 256 * 256);
	while (y < wstart && y < ((d->m->resy - 1) / 2))
	{
		ft_put_pixel_img(d->thisframe, x, y, colour);
		y++;
	}
	while (y < wend && y < d->m->resy)
	{
		colour = ft_gettexel(d, y, wstart, wend);
		ft_put_pixel_img(d->thisframe, x, y, colour);
		y++;
	}
	colour = (d->m->fb + d->m->fg * 256 + d->m->fr * 256 * 256);
	while (y < d->m->resy)
	{
		ft_put_pixel_img(d->thisframe, x, y, colour);
		y++;
	}
	return (0);
}

int		ft_gettexel(t_data *d, double y, int wstart, int wend)
{
	t_img	tex;
	char	*texel;
	double	x;

	tex = d->tex.wtex;
	tex = (d->r.pole == 1 && d->r.rydir < 0) ? d->tex.stex : tex;
	tex = (d->r.pole == 1 && d->r.rydir >= 0) ? d->tex.ntex : tex;
	tex = (d->r.pole == 0 && d->r.rxdir < 0) ? d->tex.etex : tex;
	if (d->r.pole == 1)
		x = (double)(d->r.pxpos + d->r.camraylen * d->r.rxdir);
	else
		x = (double)(d->r.pypos + d->r.camraylen * d->r.rydir);
	x = (double)((x - floor(x)) * tex.width);
	if ((d->r.pole == 0 && d->r.rxdir < 0) || \
	(d->r.pole == 1 && d->r.rydir >= 0))
		x = tex.width - x;
	y = (((y - wstart) / (double)(wend - wstart)) * 2 - 1) \
	* (tex.height / 2);
	y = (d->r.camraylen <= 1) ? y * d->r.camraylen : y;
	y = y + (tex.height / 2);
	texel = tex.addr + ((int)y * tex.line_bytes + \
	(int)x * (tex.bits_per_pixel / 8));
	return (*(unsigned int*)texel);
}
