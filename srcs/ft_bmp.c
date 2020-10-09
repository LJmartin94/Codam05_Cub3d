/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/09 16:23:31 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/09 19:43:21 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_metadata(t_data *d);

int	ft_checksave(char *arg, t_mapinfo *m)
{
	if ((arg == ft_strstr(arg, "--save")))
		m->snapshot = 1;
	if (m->snapshot)
		m->snapshot = (arg[6] == '\0') ? m->snapshot : 0;
	return (m->snapshot);
}

int	ft_makebmp(t_data *d)
{
	d->bmpfd = open("snapshot.bmp", O_CREAT, O_WRONLY, O_TRUNC, 0644);
	if (d->bmpfd == -1)
		xt_wrerror(d->m);
	ft_metadata(d);
}

int	ft_metadata(t_data *d)
{
	int 			i;
	unsigned char	meta[54];
	int 			size;

	i = 0;
	while (i < 54)
	{
		meta[i] = (unsigned char)(0);
		i++;
	}
	meta[0] = (unsigned char)('B');
	meta[1] = (unsigned char)('M');
	size = 54 + d->imga.bits_per_pixel * d->m->resx * d->m->resy;
	ft_int_in_bytes(size, &(meta[2]));
	ft_int_in_bytes(54, &(meta[10]));
	
	// https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
	
}

int ft_int_in_bytes(int num, unsigned char *dest)
{

}
