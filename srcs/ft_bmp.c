/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 16:23:31 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/13 14:43:23 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_makebmp(t_data *d)
{
	if (d->imga.bits_per_pixel <= 8)
		xt_bpp_error(d->m);
	d->bmpfd = open("snapshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (d->bmpfd == -1)
		xt_wrerror(d->m);
	d->frame = 1;
	ft_castray(d);
	ft_handlesprites(d);
	ft_metadata(d);
	ft_img_to_bmp(d);
	return (0);
}

int	xt_bpp_error(t_mapinfo *m)
{
	errno = 12;
	perror("Error\nThe bits per pixel specified by your machine's \
	architecture are too low, palletised BMP images are not handled.\n");
	xt_quit(1, m);
	return (1);
}

/*
** For more information on what metadata is being stored
** in the header of this file, visit
** https://medium.com/sysf/
** bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
*/

int	ft_metadata(t_data *d)
{
	int				i;
	unsigned char	meta[54];
	int				size;

	i = 0;
	while (i < 54)
	{
		meta[i] = (unsigned char)(0);
		i++;
	}
	meta[0] = (unsigned char)('B');
	meta[1] = (unsigned char)('M');
	size = 54 + (d->imga.bits_per_pixel / 8) * d->m->resx * d->m->resy;
	ft_int_in_bytes(size, &(meta[2]));
	ft_int_in_bytes(54, &(meta[10]));
	ft_int_in_bytes(40, &(meta[14]));
	ft_int_in_bytes(d->m->resx, &(meta[18]));
	ft_int_in_bytes(d->m->resy, &(meta[22]));
	ft_int_in_bytes(1, &(meta[26]));
	ft_int_in_bytes(d->imga.bits_per_pixel, &(meta[28]));
	i = write(d->bmpfd, meta, 54);
	if (i == -1)
		xt_wrerror(d->m);
	return (0);
}

int	ft_int_in_bytes(int num, unsigned char *dest)
{
	dest[0] = (unsigned char)(num);
	dest[1] = (unsigned char)(num >> 8);
	dest[2] = (unsigned char)(num >> 16);
	dest[3] = (unsigned char)(num >> 24);
	return (0);
}

int	ft_img_to_bmp(t_data *d)
{
	int size;
	int yaddr;
	int w;
	int y;

	size = (d->imga.bits_per_pixel / 8) * d->m->resx;
	y = d->m->resy - 1;
	while (y >= 0)
	{
		yaddr = y * (d->imga.line_bytes);
		w = write(d->bmpfd, &(d->imga.addr[yaddr]), size);
		if (w == -1)
			xt_wrerror(d->m);
		y--;
	}
	return (0);
}
