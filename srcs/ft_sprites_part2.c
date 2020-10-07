/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sprites_part2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/28 16:49:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/07 18:35:04 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

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
	d->rsp.height = (d->rsp.height < 1) ? 1 : d->rsp.height;
	d->rsp.startspy = -d->rsp.height / 2 + (d->m->resy - 1) / 2;
	d->rsp.startspy = (d->rsp.startspy < 0) ? 0 : d->rsp.startspy;
	d->rsp.endspy = d->rsp.height / 2 + (d->m->resy - 1) / 2;
	d->rsp.endspy = (d->rsp.endspy > d->m->resy) ? d->m->resy : d->rsp.endspy;
	d->rsp.width = (ratio >= 1) ? size : size * ratio;
	d->rsp.width = (d->rsp.width < 1) ? 1 : d->rsp.width;
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
				// printf("ty = %d\n", d->rsp.ty);
				// printf("ty = ( [y] %d - [(int)((d->m->resy - 1) / 2)] %d + [d->rsp.height / 2] %f ) * [d->tex.sptex.height] %d / [d->rsp.height] %f\n", y, (int)((d->m->resy - 1) / 2), (d->rsp.height / 2), d->tex.sptex.height, d->rsp.height);
				d->rsp.ty = (256 * (y - (int)((d->m->resy - 1) / 2) +\
				(d->rsp.height + 1) / 2) * d->tex.sptex.height / d->rsp.height) / 256;
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
