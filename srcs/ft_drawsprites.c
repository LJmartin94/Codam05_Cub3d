/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_drawsprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 16:49:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/29 10:58:33 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_scanforsprites(t_data *d)
{
	int y;
	int x;
	int s;

	y = 0;
	s = 0;
	while (d->m->map[y] != NULL)
	{
		x = 0;
		while (d->m->map[y][x] != '\0')
		{
			if (d->m->map[y][x] == '2' && d->m->copy->map[y][x] == 'x')
			{
				d->m->sprites[s].y = y;
				d->m->sprites[s].x = x;
				s++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_drawsprites(t_data *d)
{
	d->frame = d->frame;
}
