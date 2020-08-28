/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_movement.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:06:36 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/28 20:05:34 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_checkcollision(t_data *d);

void	ft_wasd(t_data *d)
{
	if (d->md.perpmov == -1)
	{
		d->md.newpx = d->r.pxpos + (d->r.pxdir * d->md.movspd);
		d->md.newpy = d->r.pypos + (d->r.pydir * d->md.movspd);
	}
	ft_checkcollision(d);
	if (d->md.perpmov == 1)
	{
		d->md.newpx = d->r.pxpos - (d->r.pxdir * d->md.movspd);
		d->md.newpy = d->r.pypos - (d->r.pydir * d->md.movspd);
	}
	ft_checkcollision(d);
	if (d->md.parmov == 1)
	{
		d->md.newpx = d->r.pxpos + (d->r.pydir * d->md.movspd * -1);
		d->md.newpy = d->r.pypos + (d->r.pxdir * d->md.movspd);
	}
	ft_checkcollision(d);
	if (d->md.parmov == -1)
	{
		d->md.newpx = d->r.pxpos + (d->r.pydir * d->md.movspd);
		d->md.newpy = d->r.pypos + (d->r.pxdir * d->md.movspd * -1);
	}
	ft_checkcollision(d);
}

void	ft_checkcollision(t_data *d)
{
	if (d->m->map[(int)d->r.pypos][(int)d->md.newpx] == '0')
		d->r.pxpos = d->md.newpx;
	if (d->m->map[(int)d->md.newpy][(int)d->r.pxpos] == '0')
		d->r.pypos = d->md.newpy;
}

void	ft_rot(t_data *d)
{
	if (d->md.rotating != 0)
	{
		d->md.prevx = d->r.pxdir;
		d->r.pxdir = d->r.pxdir * cos(d->md.rotspd) - d->r.pydir * \
		sin(d->md.rotspd) * d->md.rotating;
		d->r.pydir = d->r.pydir * cos(d->md.rotspd) + d->md.prevx * \
		sin(d->md.rotspd) * d->md.rotating;
		d->md.prevx = d->r.xplane;
		d->r.xplane = d->r.xplane * cos(d->md.rotspd) - d->r.yplane * \
		sin(d->md.rotspd) * d->md.rotating;
		d->r.yplane = d->r.yplane * cos(d->md.rotspd) + d->md.prevx * \
		sin(d->md.rotspd) * d->md.rotating;
	}
}
