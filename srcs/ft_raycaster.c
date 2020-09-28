/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_raycaster.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 19:25:59 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/28 14:10:42 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
		d->r.hit = (d->m->map[d->r.rypos][d->r.rxpos] == '1') ? 1 : 0;
	}
	return (0);
}
