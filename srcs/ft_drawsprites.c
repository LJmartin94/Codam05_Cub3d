/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_drawsprites.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 16:49:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/06 17:37:49 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_scanforsprites(t_data *d);
void	ft_handlesprites(t_data *d);
void	ft_sortsprites(t_sprite **sprite, int l, int r, t_sprite val);
int		ft_orientsprite(t_data *d, int s);
int		ft_getspritedims(t_data *d);
int		ft_overlaysprite(t_data *d);
int		ft_getspritetexel(t_data *d, int texX, int texY);

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
	d->rsp.spmidx = (int)((d->m->resx / 2) * (1 + xsprite / ysprite));
	d->rsp.depth = ysprite;
	return (0);
}

int		ft_getspritedims(t_data *d)
{
	double	ratio;
	double	size;

	ratio = (double)(d->tex.sptex.width) / (d->tex.sptex.height);
	if (d->m->resy <= d->m->resx)
		size = abs((int)(d->m->resy / (d->rsp.depth)));
	else
		size = abs((int)(d->m->resx / (d->rsp.depth)));
	d->rsp.height = (ratio <= 1) ? size : size / ratio;
	d->rsp.startspy = -d->rsp.height / 2 + d->m->resy / 2;
	d->rsp.startspy = (d->rsp.startspy < 0) ? 0 : d->rsp.startspy;
	d->rsp.endspy = d->rsp.height / 2 + d->m->resy / 2;
	d->rsp.endspy = (d->rsp.endspy > d->m->resy) ? d->m->resy : d->rsp.endspy;
	d->rsp.width = (ratio >= 1) ? size : size * ratio;
	d->rsp.startspx = -d->rsp.width / 2 + d->rsp.spmidx;
	d->rsp.startspx = (d->rsp.startspx < 0) ? 0 : d->rsp.startspx;
	d->rsp.endspx = d->rsp.width / 2 + d->rsp.spmidx;
	d->rsp.endspx = (d->rsp.endspx > d->m->resx) ? d->m->resx : d->rsp.endspx;
	return (0);
}

int		ft_overlaysprite(t_data *d)
{
	int		wixel;
	int		y;

	wixel = d->rsp.startspx;
	while (wixel < d->rsp.endspx)
	{
		d->rsp.tx = (int)(256 * (wixel - (-d->rsp.width / 2 + d->rsp.spmidx)) \
			* d->tex.sptex.width / d->rsp.width) / 256;
		if (d->rsp.depth > 0 && d->rsp.depth < d->m->zbuf[wixel] \
			&& wixel >= 0 && wixel < d->m->resx)
		{
			y = d->rsp.startspy;
			while (y < d->rsp.endspy)
			{
				d->rsp.ty = (256 * (y - d->m->resy / 2.0 + d->rsp.height / 2) \
					* d->tex.sptex.height / d->rsp.height) / 256;
				d->rsp.colour = ft_getspritetexel(d, d->rsp.tx, d->rsp.ty);
				if (d->rsp.colour != 0x00000000)
					ft_put_pixel_img(d->rsp.towrite, wixel, y, d->rsp.colour);
				y++;
			}
		}
		wixel++;
	}
	return (0);
}

int		ft_getspritetexel(t_data *d, int xtex, int ytex)
{
	t_img	tex;
	char	*texel;

	tex = d->tex.sptex;
	texel = tex.addr + (ytex * tex.line_bytes + \
	xtex * (tex.bits_per_pixel / 8));
	return (*(unsigned int*)texel);
}
