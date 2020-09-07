/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/07 15:47:20 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_gettexel(t_data *d, int x, int y);

void	ft_castray(t_data *d)
{
	int x;

	x = 0;
	while (x <= d->m->resx)
	{
		d->r.wixel = -1 + (x / (double)d->m->resx) * 2;
		d->r.rxdir = d->r.pxdir + d->r.xplane * d->r.wixel;
		d->r.rydir = d->r.pydir + d->r.yplane * d->r.wixel;
		d->r.rxpos = (int)d->r.pxpos;
		d->r.rypos = (int)d->r.pypos;
		d->r.nsdelta = (d->r.rydir == 0) ? 1 : 0;
		d->r.wedelta = (d->r.rxdir == 0) ? 1 : 0;
		if (d->r.rxdir != 0 && d->r.rydir != 0)
		{
			d->r.wedelta = sqrt(1 + (d->r.rydir * d->r.rydir) / \
			(d->r.rxdir * d->r.rxdir));
			d->r.nsdelta = sqrt(1 + (d->r.rxdir * d->r.rxdir) / \
			(d->r.rydir * d->r.rydir));
		}
		ft_ppostobox(d);
		ft_findwall(d);
		ft_colourwixel(d, x);
		x++;
	}
}

int		ft_ppostobox(t_data *d)
{
	d->r.stepx = 0;
	d->r.stepy = 0;
	d->r.weside = 0;
	d->r.nsside = 0;
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
		colour = ft_gettexel(d, x, y);
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

int		ft_gettexel(t_data *d, int x, int y)
{
	t_img	tex;
	int		pxl_mem_size;
	char	*texel;
	int colour;

	y = 1;
	x = 15;
	tex = (d->r.pole == 1) ? d->tex.stex : d->tex.wtex; //only differentiating between NS/WE
	pxl_mem_size = (tex.bits_per_pixel / 8);
	texel = tex.addr + (y * tex.line_bytes + x * pxl_mem_size); //grabbing arbitrary x and y where the textures differ notably
	colour = *(unsigned int*)texel;
	return (colour);
}

// void	ft_put_pixel_img(t_img *img, int x, int y, int colour)
// {
// 	char	*dst;
// 	int		pxl_mem_size;

// 	pxl_mem_size = (img->bits_per_pixel / 8);
// 	dst = img->addr + (y * img->line_bytes + x * pxl_mem_size);
// 	*(unsigned int*)dst = colour;
// }
