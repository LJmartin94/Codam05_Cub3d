/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_mlx.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/07 14:20:31 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/28 14:24:25 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_mlx_run(t_data *data)
{
	if (data->md.perpmov != 0 || data->md.parmov != 0)
		ft_wasd(data);
	if (data->md.rotating != 0)
		ft_rot(data);
	ft_update_window(data);
	return (0);
}
