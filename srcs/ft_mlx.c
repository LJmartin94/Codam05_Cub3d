/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mlx.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 14:20:31 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/18 18:38:23 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_mlx_run(t_data *data)
{
	ft_castray(data);
	data->frame++;
	if (data->frame % 2 == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->imga.cont, 0, 0);
	else
		mlx_put_image_to_window(data->mlx, data->win, data->imgb.cont, 0, 0);
	return (0);
}
