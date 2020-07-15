/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser_part1.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 18:41:20 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/15 07:57:25 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

t_mapinfo	ft_constructor(t_mapinfo mapinfo)
{
	mapinfo.noerror = 1;
	mapinfo.resx = -1;
	mapinfo.resy = -1;
	mapinfo.northtex = NULL;
	mapinfo.southtex = NULL;
	mapinfo.westtex = NULL;
	mapinfo.easttex = NULL;
	mapinfo.spritetex = NULL;
	mapinfo.fr = -1;
	mapinfo.fg = -1;
	mapinfo.fb = -1;
	mapinfo.cr = -1;
	mapinfo.cg = -1;
	mapinfo.cb = -1;
	mapinfo.facing = '\0';
	mapinfo.mapstart = 0;
	mapinfo.ydim = 1;
	mapinfo.map = NULL;
	return (mapinfo);
}

void		ft_parser(t_mapinfo *m)
{
	char	*line;
	int		i;
	char	tag;

	while (get_next_line(m->fd, &line) && m->noerror)
	{
		i = 0;
		if (ft_elemxref(m, '0'))
			m->mapstart++;
		else
			m->ydim++;
		while (line[i] != '\0' && ft_elemxref(m, '0'))
		{
			ft_skipspace(line, &i);
			tag = ft_gettag(line, &i);
			ft_writevals(m, tag, line, &i);
			if (m->noerror == 0)
				break ;
		}
		free(line);
	}
	free(line);
	if (m->noerror == 0)
		ft_parserror(1, m);
}

int			ft_elemxref(t_mapinfo *mapinfo, char flag)
{
	int ret;

	ret = 0;
	if ((flag == '0' || flag == 'r') && mapinfo->resx == -1)
		ret = 1;
	if ((flag == '0' || flag == 'N') && mapinfo->northtex == NULL)
		ret = 1;
	if ((flag == '0' || flag == 'S') && mapinfo->southtex == NULL)
		ret = 1;
	if ((flag == '0' || flag == 'W') && mapinfo->westtex == NULL)
		ret = 1;
	if ((flag == '0' || flag == 'E') && mapinfo->easttex == NULL)
		ret = 1;
	if ((flag == '0' || flag == 's') && mapinfo->spritetex == NULL)
		ret = 1;
	if ((flag == '0' || flag == 'f') && mapinfo->fr == -1)
		ret = 1;
	if ((flag == '0' || flag == 'c') && mapinfo->cr == -1)
		ret = 1;
	return (ret);
}

int			ft_skipspace(char *line, int *i)
{
	while ((line[*i] == '\f') || (line[*i] == '\r') || (line[*i] == '\n') \
	|| (line[*i] == '\t') || (line[*i] == '\v') || (line[*i] == ' '))
	{
		(*i)++;
	}
	return (0);
}
