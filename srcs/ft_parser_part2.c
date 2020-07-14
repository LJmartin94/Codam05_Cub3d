/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_parser_part2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 12:47:12 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/14 17:25:42 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

char		ft_gettag(char *line, int *i)
{
	if (&(line[*i]) == ft_strstr(&(line[*i]), "R "))
		return ('r');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "NO "))
		return ('N');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "SO "))
		return ('S');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "WE "))
		return ('W');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "EA "))
		return ('E');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "S "))
		return ('s');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "F "))
		return ('f');
	else if (&(line[*i]) == ft_strstr(&(line[*i]), "C "))
		return ('c');
	else
		return ('0');
}

int			ft_writevals(t_mapinfo *mapinfo, char tag, char *line, int *i)
{
	if (tag == '0' || !(ft_elemxref(mapinfo, tag)))
	{
		mapinfo->noerror = 0;
		return (0);
	}
	while (line[*i] != ' ')
		(*i)++;
	(*i)++;
	if (tag == 'N' || tag == 'S' || tag == 'W' || tag == 'E' || tag == 's')
		ft_fetchpath(mapinfo, tag, line, i);
	else if (tag == 'f' || tag == 'c')
		ft_fetchclr(mapinfo, tag, line, i);
	else if (tag == 'r')
		ft_fetchres(mapinfo, line, i);
	return (0);
}

void		ft_fetchpath(t_mapinfo *m, char tag, char *line, int *i)
{
	int		pathfd;
	int		j;
	char	*validpath;

	pathfd = open(&(line[*i]), O_RDONLY);
	m->noerror = (pathfd == -1) ? 0 : m->noerror;
	if (pathfd != -1)
		close(pathfd);
	j = ft_linelen(&(line[*i]), '\0');
	validpath = (char *)malloc(sizeof(char) * (j + 1));
	if (validpath == 0)
		return ;
	j = 0;
	while (line[*i] != '\0')
	{
		validpath[j] = line[*i];
		j++;
		(*i)++;
	}
	validpath[j] = '\0';
	m->northtex = (tag == 'N') ? validpath : m->northtex;
	m->southtex = (tag == 'S') ? validpath : m->southtex;
	m->westtex = (tag == 'W') ? validpath : m->westtex;
	m->easttex = (tag == 'E') ? validpath : m->easttex;
	m->spritetex = (tag == 's') ? validpath : m->spritetex;
}

int			ft_fetchclr(t_mapinfo *m, char tag, char *line, int *i)
{
	while ((line[*i] >= '0' && line[*i] <= '9'))
	{
		m->x = 0;
		while ((line[*i] >= '0') && (line[*i] <= '9'))
		{
			m->x = (line[*i] - '0') + (m->x * 10);
			(*i)++;
			m->noerror = (m->x > 255) ? 0 : m->noerror;
		}
		m->fb = (tag == 'f' && m->fb == -1 && m->fg != -1) ? m->x : m->fb;
		m->fg = (tag == 'f' && m->fg == -1 && m->fr != -1) ? m->x : m->fg;
		m->fr = (tag == 'f' && m->fr == -1) ? m->x : m->fr;
		if (tag == 'f' && m->fb != -1)
			break ;
		m->cb = (tag == 'c' && m->cb == -1 && m->cg != -1) ? m->x : m->cb;
		m->cg = (tag == 'c' && m->cg == -1 && m->cr != -1) ? m->x : m->cg;
		m->cr = (tag == 'c' && m->cr == -1) ? m->x : m->cr;
		if (tag == 'c' && m->cb != -1)
			break ;
		if (line[*i] == ',' && line[*i - 1] >= '0' && line[*i - 1] <= '9')
			(*i)++;
	}
	m->noerror = ((tag == 'f' && m->fb == -1) || \
	(tag == 'c' && m->cb == -1)) ? 0 : m->noerror;
	return (0);
}

int			ft_fetchres(t_mapinfo *mapinfo, char *line, int *i)
{
	while ((line[*i] >= '0') && (line[*i] <= '9'))
	{
		if (mapinfo->resx == -1)
			mapinfo->resx = 0;
		mapinfo->resx = (line[*i] - '0') + (mapinfo->resx * 10);
		(*i)++;
	}
	if (line[*i] == ' ')
		(*i)++;
	while ((line[*i] >= '0') && (line[*i] <= '9'))
	{
		if (mapinfo->resy == -1)
			mapinfo->resy = 0;
		mapinfo->resy = (line[*i] - '0') + (mapinfo->resy * 10);
		(*i)++;
	}
	if ((mapinfo->resx < 1) || (mapinfo->resy < 1))
		mapinfo->noerror = 0;
	return (0);
}
