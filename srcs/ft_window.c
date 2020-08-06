/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:39:24 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/06 17:46:19 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_heavensplit(t_mapinfo *m, t_img imga);

void	ft_resize(void *mlx, t_mapinfo *m);

int		ft_window(t_mapinfo *m)
{
	void	*mlx;
	void	*mlx_win;
	t_img	imga;

	mlx = mlx_init();
	if (mlx == 0)
		xt_mlxerror(m);
	ft_resize(mlx, m);
	mlx_win = mlx_new_window(mlx, m->resx, m->resy, "Test");
	if (mlx_win == 0)
		xt_mlxerror(m);
	imga.cont = mlx_new_image(mlx, m->resx, m->resy);
	imga.addr = mlx_get_data_addr(imga.cont, &imga.bits_per_pixel, \
	&imga.line_bytes, &imga.endian);
	ft_heavensplit(m, imga);
	mlx_put_image_to_window(mlx, mlx_win, imga.cont, 0, 0);
	mlx_loop(mlx);
	return (0);
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

void	ft_put_pixel_img(t_img *img, int x, int y, int colour)
{
	char	*dst;
	int		pxl_mem_size;

	pxl_mem_size = (img->bits_per_pixel / 8);
	dst = img->addr + (y * img->line_bytes + x * pxl_mem_size);
	*(unsigned int*)dst = colour;
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
