/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_keyhook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/22 16:50:46 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/31 15:29:26 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_listen_for_event(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, &ft_pressed, data);
	mlx_hook(data->win, 3, 1L << 1, &ft_release, data);
	return (0);
}

int		ft_pressed(int key, t_data *d)
{
	if (key == W || key == UP)
		d->md.v = -1;
	else if (key == S || key == DOWN)
		d->md.v = 1;
	else if (key == A)
		d->md.h = -1;
	else if (key == D)
		d->md.h = 1;
	else if (key == LEFT)
		d->md.rotating = -1;
	else if (key == RIGHT)
		d->md.rotating = 1;
	else if (key == ESC)
		xt_quit(0, d->m);
	return (0);
}

int		ft_release(int key, t_data *d)
{
	if (key == W || key == UP)
		d->md.v = 0;
	else if (key == S || key == DOWN)
		d->md.v = 0;
	else if (key == A)
		d->md.h = 0;
	else if (key == D)
		d->md.h = 0;
	else if (key == LEFT)
		d->md.rotating = 0;
	else if (key == RIGHT)
		d->md.rotating = 0;
	else if (key == ESC)
		xt_quit(0, d->m);
	return (0);
}
