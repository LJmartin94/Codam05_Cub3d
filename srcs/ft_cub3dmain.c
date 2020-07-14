/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cub3dmain.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 18:42:12 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/14 17:29:47 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_printall(t_mapinfo *m)
{
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

	// char	facing;
	// int		mapstart;
	// int		mapxdim;
	// int		mapydim;
	return (0);
}

int		main(int argc, char **argv)
{
	t_mapinfo	mapinfo;

	mapinfo = ft_constructor(mapinfo);
	mapinfo.fd = open(argv[1], O_RDONLY);
	ft_prelimcheck(argc, argv[1], &mapinfo);
	ft_parser(&mapinfo);
	ft_printall(&mapinfo);
	ft_quit(0, &mapinfo);
}
