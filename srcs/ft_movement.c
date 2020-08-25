/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_movement.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 13:06:36 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/25 15:45:49 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_wasd(t_data *d, int key)
{
	if (key == W)
	{
		d->md.newpx = d->r.pxpos + (d->r.pxdir * d->md.speed);
		d->md.newpy = d->r.pypos + (d->r.pydir * d->md.speed);
	}
	if (key == S)
	{
		d->md.newpx = d->r.pxpos - (d->r.pxdir * d->md.speed);
		d->md.newpy = d->r.pypos - (d->r.pydir * d->md.speed);
	}
	if (key == D)
	{
		d->md.newpx = d->r.pxpos + (d->r.pydir * d->md.speed * -1);
		d->md.newpy = d->r.pypos + (d->r.pxdir * d->md.speed);
	}
	if (key == A)
	{
		d->md.newpx = d->r.pxpos + (d->r.pydir * d->md.speed);
		d->md.newpy = d->r.pypos + (d->r.pxdir * d->md.speed * -1);
	}
	if (d->m->map[(int)d->r.pypos][(int)d->md.newpx] == '0')
		d->r.pxpos = d->md.newpx;
	if (d->m->map[(int)d->md.newpy][(int)d->r.pxpos] == '0')
		d->r.pypos = d->md.newpy;
}
