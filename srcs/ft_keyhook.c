/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_keyhook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/22 16:50:46 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/27 17:47:07 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_release(int key, t_data *d);

int		ft_listen_for_event(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, &ft_event_switchboard, data); //pressed
	mlx_hook(data->win, 3, 1L << 0, &ft_release, data); //released
	return (0);
}

int		ft_event_switchboard(int key, t_data *d)
{
	d->md.pressed = 1;
	d->md.speed = 0.2;
	d->md.rot = 0.2;
	if (key == W || key == A || key == S || key == D || \
	key == UP || key == DOWN)
		ft_wasd(d, key);
	else if (key == LEFT || key == RIGHT)
		ft_rot(d, key);
	else if (key == ESC)
		xt_quit(0, d->m);
	else if (LINUX == 1)
		printf("A key was pressed (linux): %d %d\n", key, LINUX);
	if (LINUX == 0)
		printf("A key was pressed (mac): %d %d\n", key, LINUX);
	return (0);
}

int		ft_release(int key, t_data *d)
{
	printf("Key %d was released\n", key);
	return (d->m->x); //filler
}
