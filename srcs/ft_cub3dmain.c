/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3dmain.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 18:42:12 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/08 17:08:01 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		main(int argc, char **argv)
{
	t_mapinfo	mapinfo;
	t_data		d;

	mapinfo = ft_constructor(&mapinfo);
	mapinfo.fd = open(argv[1], O_RDONLY);
	ft_prelimcheck(argc, argv[1], &mapinfo);
	ft_parser(&mapinfo);
	ft_processmap(&mapinfo, argv[1]);
	d = ft_window(&mapinfo);
	ft_initraydata(&(d.r), d.m);
	ft_scanforsprites(&d);
	ft_getmovin(&d);
	ft_getteximgs(&d);
	ft_listen_for_event(&d);
	mlx_loop_hook(d.mlx, &ft_mlx_run, &d);
	mlx_loop(d.mlx);
	xt_quit(0, &mapinfo);
}
