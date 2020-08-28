/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3dmain.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 18:42:12 by limartin      #+#    #+#                 */
/*   Updated: 2020/08/28 14:19:47 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_printall(t_mapinfo *m)
{
	int i;

	i = 0;
	printf("Struct ID:	%p\n", m);
	printf("No error: 	%d\n", m->noerror);
	printf("Fd: 		%d\n", m->fd);
	printf("Resx: 		%ld\n", m->resx);
	printf("Resy: 		%ld\n", m->resy);

	printf("NO: 		%s\n", m->northtex);
	printf("SO: 		%s\n", m->southtex);
	printf("WE: 		%s\n", m->westtex);
	printf("EA: 		%s\n", m->easttex);
	printf("S: 		%s\n", m->spritetex);

	printf("F:		%d,%d,%d\n", m->fr, m->fg, m->fb);
	printf("C:		%d,%d,%d\n", m->cr, m->cg, m->cb);
	printf("Calc var:	%d\n", m->x);

	printf("Map start:	%d\n", m->mapstart);
	printf("Map Y dim:	%d\n", m->ydim);
	printf("Struct cpy:	%p\n", m->copy);
	printf("Char **map:	%p\n", m->map);
	printf("Contents of map:\n");
	while (m->map[i] != NULL)
	{
		printf("|%s|\n", m->map[i]);
		i++;
	}
	
	// char	facing;

	// i = 0;
	// while (i < 107)
	// {
	// 	errno = i;
	// 	printf("Error %d:\n", i);
	// 	perror("Error");
	// 	i++;
	// }
	return (0);
}

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
	ft_listen_for_event(&d);
	mlx_loop_hook(d.mlx, &ft_mlx_run, &d);
	mlx_loop(d.mlx);
	//ft_printall(&mapinfo);
	xt_quit(0, &mapinfo);
}
