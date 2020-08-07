/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:39:24 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/07 14:21:41 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_heavensplit(t_mapinfo *m, t_img imga);

t_data	ft_window(t_mapinfo *m)
{
	t_data	d;

	d.m = m;
	d.mlx = mlx_init();
	if (d.mlx == 0)
		xt_mlxerror(m);
	ft_resize(d.mlx, d.m);
	d.win = mlx_new_window(d.mlx, d.m->resx, d.m->resy, "Test");
	if (d.win == 0)
		xt_mlxerror(m);
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
	mlx_get_screen_size(mlx, &x, &y);
	if (x < m->resx)
		m->resx = x;
	if (y < m->resy)
		m->resy = y;
}

void	ft_createimgs(t_img *a, t_img *b, void *mlx, t_mapinfo *m)
{
	a->cont = mlx_new_image(mlx, m->resx, m->resy);
	a->addr = mlx_get_data_addr(a->cont, &a->bits_per_pixel, \
	&a->line_bytes, &a->endian);
	ft_heavensplit(m, *a);
	b->cont = mlx_new_image(mlx, m->resx, m->resy);
	b->addr = mlx_get_data_addr(b->cont, &b->bits_per_pixel, \
	&b->line_bytes, &b->endian);
	ft_heavensplit(m, *b);
}

void	ft_heavensplit(t_mapinfo *m, t_img imga)
{
	int		x;
	int		y;
	int		colour;

	colour = ((m->cb) + (m->cg * 16 * 16) + (m->cr * 16 * 16 * 16 * 16));
	y = 0;
	while (y < m->resy)
	{
		x = 0;
		while (x < m->resx)
		{
			ft_put_pixel_img(&imga, x, y, colour);
			x++;
		}
		y++;
		if (y >= (m->resy / 2))
			colour = ((m->fb) + (m->fg * 256) + (m->fr * 256 * 256));
	}
}

void	ft_put_pixel_img(t_img *img, int x, int y, int colour)
{
	char	*dst;
	int		pxl_mem_size;

	pxl_mem_size = (img->bits_per_pixel / 8);
	dst = img->addr + (y * img->line_bytes + x * pxl_mem_size);
	*(unsigned int*)dst = colour;
}
