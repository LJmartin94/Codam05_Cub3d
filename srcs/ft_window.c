/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:39:24 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/27 19:17:09 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_window(t_mapinfo *m)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	if (mlx == 0)
		xt_mlxerror(m);
	mlx_win = mlx_new_window(mlx, m->resx, m->resy, "Test");
	if (mlx_win == 0)
		xt_mlxerror(m);
	mlx_loop(mlx);

	t_img	imga;
	imga.cont = mlx_new_image(mlx, m->resx, m->resy);
	imga.addr = mlx_get_data_addr(imga.cont, &imga.bits_per_pixel, \
	&imga.line_length, &imga.endian)

	ft_put_pixel_img();
	return (0);
}

void	ft_put_pixel_img()
{
}