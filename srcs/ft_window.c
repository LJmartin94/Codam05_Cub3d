/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:39:24 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/09 15:25:33 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_data	ft_window(t_mapinfo *m)
{
	t_data	d;

	d.m = m;
	d.mlx = mlx_init();
	if (d.mlx == 0)
		xt_mlxerror(m);
	ft_resize(d.mlx, d.m);
	if (!(m->snapshot))
	{
		d.win = mlx_new_window(d.mlx, d.m->resx, d.m->resy, "💧🌱Cub3D🔥💨");
		if (d.win == 0)
			xt_mlxerror(m);
	}
	ft_createimgs(&(d.imga), &(d.imgb), d.mlx, d.m);
	d.frame = -1;
	return (d);
}

void	ft_resize(void *mlx, t_mapinfo *m)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (!(m->snapshot))
	{
		mlx_get_screen_size(mlx, &x, &y);
		if (x < m->resx)
			m->resx = x;
		if (y < m->resy)
			m->resy = y;
	}
	if (m->resx > 16384 || m->resy > 16384)
		xt_mlxerror(m);
}

void	ft_createimgs(t_img *a, t_img *b, void *mlx, t_mapinfo *m)
{
	a->cont = mlx_new_image(mlx, m->resx, m->resy);
	a->addr = mlx_get_data_addr(a->cont, &a->bits_per_pixel, \
	&a->line_bytes, &a->endian);
	b->cont = mlx_new_image(mlx, m->resx, m->resy);
	b->addr = mlx_get_data_addr(b->cont, &b->bits_per_pixel, \
	&b->line_bytes, &b->endian);
}

void	ft_put_pixel_img(t_img *img, int x, int y, int colour)
{
	char	*dst;
	int		pxl_mem_size;

	pxl_mem_size = (img->bits_per_pixel / 8);
	dst = img->addr + (y * img->line_bytes + x * pxl_mem_size);
	if (colour >= 0x00000000 && (unsigned int)colour <= 0x00FFFFFF)
		*(unsigned int*)dst = colour;
	else
		*(unsigned int*)dst = 0x00000000;
}

void	ft_update_window(t_data *data)
{
	ft_castray(data);
	ft_handlesprites(data);
	data->frame++;
	if (data->frame % 2 == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->imga.cont, 0, 0);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->imgb.cont, 0, 0);
}
