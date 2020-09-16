/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/16 14:06:51 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_gettexel(t_data *d, int y, int wstart, int wend);

void	ft_castray(t_data *d)
{
	int x;

	x = 0;
	while (x < d->m->resx)
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
	while (y < wend)
	{
		colour = ft_gettexel(d, y, wstart, wend);
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

int		ft_gettexel(t_data *d, int y, int wstart, int wend)
{
	t_img	tex;
	char	*texel;
	double	x;
	int		colour;

	if (d->r.pole == 1 && d->r.rydir < 0)
		tex = d->tex.stex;
	else if (d->r.pole == 1 && d->r.rydir >= 0)
		tex = d->tex.ntex;
	else if (d->r.pole == 0 && d->r.rxdir < 0)
		tex = d->tex.etex;
	else
		tex = d->tex.wtex;
	if (d->r.pole == 1)
		x = (double)(d->r.pxpos + d->r.camraylen * d->r.rxdir);
	else
		x = (double)(d->r.pypos + d->r.camraylen * d->r.rydir);
	x = (double)((x - floor(x)) * tex.width);
	if (1)
	{
		// y = (((y - wstart) / (double)(wend - wstart)) * 2 - 1) 
		// * (tex.height / 2);
		// y = (d->r.camraylen <= 1) ? y * d->r.camraylen : y;
		// y = y + (tex.height / 2);

		// double ycalc = (double)y;
		// int hwall = (int)(d->m->resy / d->r.camraylen); //height of wall relative to screen, how many screen pixels to draw (less than yres = wall is far)
		// double step = 1.0 * tex.height / hwall; //y number of pixels to skip down in the texture after drawing pixel (less than 1 = wall is close)
		// ycalc = (double)(((y - wstart) / (double)(wend - wstart)) * 2 - 1); // 
		// ycalc = (hwall >= d->m->resy) ? (double)((double) ycalc * (double)(tex.height / 2) / (double)(hwall / d->m->resy)) : (double)((double)ycalc * (double)(tex.height / 2));
		// y = (int)ycalc + (tex.height / 2);
		// hwall = step; //filler

		double ycalc = (double)y;
		ycalc = (((y - wstart) / (double)(wend - wstart)) * 2 - 1) 
		* (tex.height / 2);
		ycalc = (d->r.camraylen <= 1) ? ycalc * d->r.camraylen : ycalc;
		y = (int)ycalc + (tex.height / 2);
	}

	if (0)
	{
		//Somewhat native
		// int hwall = (int)(d->m->resy / d->r.camraylen);
		// double step = 1.0 * tex.height / hwall;
		// double texPos = (wstart - d->m->resy / 2 + hwall / 2) * step;
		// y = y - wstart;
		// //inside their loop
		// if (y > 0)
		// 	texPos = texPos + step * (y - 1);
		// int texY = (int)texPos & (tex.height - 1);
		// y = texY;

		//No need for texY variable
		int hwall = (int)(d->m->resy / d->r.camraylen); //height of wall relative to screen, how many screen pixels to draw (less than yres = wall is far)
		double step = 1.0 * tex.height / hwall; //y number of pixels to skip down in the texture after drawing pixel (less than 1 = wall is close)
		double texPos = (wstart - d->m->resy / 2 + hwall / 2) * step; //at what pixel height you start in the texture (if larger than 0, wall is close), incremented by step for each y
		y = y - wstart; //make start of the wall 0, second wall screen pixel 1 etc
		if (y > 0)
			texPos = texPos + step * (y - 1);
		y = (int)texPos & (tex.height - 1);

		//No need for texPos variable
		// int hwall = (int)(d->m->resy / d->r.camraylen);
		// double step = 1.0 * tex.height / hwall;
		// y = y - wstart;
		// y = (wstart - d->m->resy / 2 + hwall / 2) * step + step * ((y - 1) % ( y + 1));
		// y = y & (tex.height - 1);

		//No need for multiple y calculations		
		// 	int hwall = (int)(d->m->resy / d->r.camraylen);
		// 	double step = (1.0 * tex.height / hwall);
		// 	y = (int)((wstart - d->m->resy / 2 + hwall / 2) * step + step * ((y - wstart - 1) % (y - wstart + 1))) & (tex.height - 1);
	
		//One crazy one-line calculation
		//y = (int)((wstart - d->m->resy / 2 + (int)(d->m->resy / d->r.camraylen) / 2) * (1.0 * tex.height / (int)(d->m->resy / d->r.camraylen)) + (1.0 * tex.height / (int)(d->m->resy / d->r.camraylen)) * ((y - wstart - 1) % (y - wstart + 1))) & (tex.height - 1);
	}

	texel = tex.addr + (y * tex.line_bytes + (int)x * (tex.bits_per_pixel / 8));
	colour = *(unsigned int*)texel;
	return (colour);
}
