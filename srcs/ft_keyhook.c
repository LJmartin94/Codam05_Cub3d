/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_keyhook.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/22 16:50:46 by lindsay       #+#    #+#                 */
/*   Updated: 2020/08/24 18:32:42 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_test_keys(int key, t_data *data);

int		ft_listen_for_event(t_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, &ft_test_keys, data); //pressed
	mlx_hook(data->win, 3, 1L << 0, &ft_test_keys, data); //released
	return (0);
}

int		ft_test_keys(int key, t_data *data)
{
	data->frame = data->frame; //using data to stop wall wextra werror
	if (key == W)
		printf("W was pressed: %d %d\n", key, LINUX);
	else if (key == A)
		printf("A was pressed: %d %d\n", key, LINUX);
	else if (key == S)
		printf("S was pressed: %d %d\n", key, LINUX);
	else if (key == D)
		printf("D was pressed: %d %d\n", key, LINUX);
	else if (LINUX == 1)
		printf("A key was pressed (linux): %d %d\n", key, LINUX);
	if (LINUX == 0)
		printf("A key was pressed (mac): %d %d\n", key, LINUX);
	return (0);
}
