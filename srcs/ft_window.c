/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_window.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 15:39:24 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/23 17:22:31 by lindsay       ########   odam.nl         */
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
	mlx_win = mlx_new_window(mlx, 800, 400, "Test");
	if (mlx_win == 0)
		xt_mlxerror(m);
	mlx_loop(mlx);
	return (0);
}
