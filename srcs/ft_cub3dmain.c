/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3dmain.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 18:42:12 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/12 19:47:06 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		main(int argc, char **argv)
{
	t_mapinfo	mapinfo;
	t_data		d;

	mapinfo = ft_constructor(&mapinfo);
	mapinfo.fd = open(argv[1], O_RDONLY);
	mapinfo.snapshot = 0;
	if (argc == 3)
		ft_checksave(argv[2], &mapinfo);
	ft_prelimcheck(argc, argv[1], &mapinfo);
	ft_parser(&mapinfo);
	ft_processmap(&mapinfo, argv[1]);
	d = ft_window(&mapinfo);
	ft_initraydata(&(d.r), d.m);
	ft_scanforsprites(&d);
	ft_getmovin(&d);
	ft_getteximgs(&d);
	if (mapinfo.snapshot == 0)
	{
		ft_listen_for_event(&d);
		mlx_loop_hook(d.mlx, &ft_mlx_run, &d);
		mlx_loop(d.mlx);
	}
	if (mapinfo.snapshot)
		ft_makebmp(&d);
	xt_quit(0, &mapinfo);
}

int	ft_checksave(char *arg, t_mapinfo *m)
{
	if ((arg == ft_strstr(arg, "--save")))
		m->snapshot = 1;
	if (m->snapshot)
		m->snapshot = (arg[6] == '\0') ? m->snapshot : 0;
	return (m->snapshot);
}
