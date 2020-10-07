/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprites_part1.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 16:49:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/07 17:55:15 by limartin      ########   odam.nl         */
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
				d->m->sprites[s].y = y + 0.5;
				d->m->sprites[s].x = x + 0.5;
				s++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_handlesprites(t_data *d)
{
	int	s;

	s = 0;
	if (d->m->spriteno <= 0)
		return ;
	while (s < d->m->spriteno)
	{
		d->m->sprites[s].dist = pow((d->r.pxpos - d->m->sprites[s].x), 2) + \
		pow((d->r.pypos - d->m->sprites[s].y), 2);
		s++;
	}
	ft_sortsprites(&(d->m->sprites), 0, d->m->spriteno - 1, d->m->sprites[0]);
	s = 0;
	d->rsp.towrite = (d->frame % 2 == 1) ? &(d->imga) : &(d->imgb);
	while (s < d->m->spriteno)
	{
		ft_orientsprite(d, s);
		ft_getspritedims(d);
		ft_overlaysprite(d);
		s++;
	}
}

void	ft_sortsprites(t_sprite **sprite, int l, int r, t_sprite val)
{
	int s;
	int ch;
	int d;

	s = l;
	ch = 0;
	d = 1;
	while (r > l)
	{
		ch = ((*sprite)[s].dist * d < (*sprite)[s + d].dist * d) ? 0 : ch + 1;
		if ((*sprite)[s].dist * d < (*sprite)[s + d].dist * d)
		{
			val = (*sprite)[s];
			(*sprite)[s] = (*sprite)[s + d];
			(*sprite)[s + d] = val;
		}
		s = s + d;
		if ((d == -1 && s == l) || (d == 1 && s == r))
		{
			d = d * -1;
			s = s + (ch + 1) * d;
			l = (d == 1) ? s : l;
			r = (d == -1) ? s : r;
		}
	}
}

int		ft_orientsprite(t_data *d, int s)
{
	double	xsprite;
	double	ysprite;
	double	xval;

	xsprite = d->m->sprites[s].x - d->r.pxpos;
	ysprite = d->m->sprites[s].y - d->r.pypos;
	xval = (1.0 / (d->r.xplane * d->r.pydir - d->r.pxdir * d->r.yplane)) * \
	(d->r.pydir * xsprite - d->r.pxdir * ysprite);
	ysprite = (1.0 / (d->r.xplane * d->r.pydir - d->r.pxdir * d->r.yplane)) * \
	(-1 * d->r.yplane * xsprite + d->r.xplane * ysprite);
	xsprite = xval;
	d->rsp.spmidx = (int)(((d->m->resx - 1) / 2) * (1 + xsprite / ysprite));
	d->rsp.depth = ysprite;
	return (0);
}
