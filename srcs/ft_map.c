/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_map.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/14 22:17:07 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/27 17:26:44 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_processmap(t_mapinfo *m, char *cub)
{
	t_mapinfo ffm;

	ft_getmap(m, cub);
	ft_scanmap(m);
	if (m->noerror == 0)
		xt_parserror(2, m);
	ft_copymap(m, &ffm);
	ft_floodfill(m->copy, m->posx, m->posy);
	if (m->copy->noerror == 0)
		xt_parserror(3, m);
	return (0);
}

int		ft_getmap(t_mapinfo *m, char *cub)
{
	char	*line;
	int		i;

	close(m->fd);
	m->fd = open(cub, O_RDONLY);
	while (m->mapstart > 0)
	{
		get_next_line(m, &line);
		m->mapstart--;
		free(line);
	}
	m->map = (char **)malloc(sizeof(char *) * (m->ydim + 1));
	if (m->map == 0)
		xt_mallocerror(m);
	i = m->ydim;
	m->ydim = 0;
	while (m->ydim < i)
	{
		get_next_line(m, &(m->map[m->ydim]));
		m->ydim++;
	}
	m->map[m->ydim] = NULL;
	return (0);
}

void	ft_scanmap(t_mapinfo *m)
{
	int i;
	int j;

	m->noerror = (m->ydim < 1) ? 0 : m->noerror;
	i = 0;
	while (m->map[i] != NULL)
	{
		j = 0;
		while (m->map[i][j] != '\0')
		{
			if (m->facing == '\0' && (m->map[i][j] == 'N' || \
		m->map[i][j] == 'S' || m->map[i][j] == 'W' || m->map[i][j] == 'E'))
			{
				m->facing = m->map[i][j];
				m->posy = i;
				m->posx = j;
			}
			else if (m->map[i][j] != ' ' && m->map[i][j] != '0' \
		&& m->map[i][j] != '1' && m->map[i][j] != '2')
				m->noerror = 0;
			j++;
		}
		i++;
	}
	m->noerror = (m->facing == '\0') ? 0 : m->noerror;
}

void	ft_copymap(t_mapinfo *org, t_mapinfo *cpy)
{
	cpy = (t_mapinfo *)malloc(sizeof(t_mapinfo));
	if (cpy == 0)
		xt_mallocerror(org);
	org->copy = cpy;
	*cpy = ft_constructor(cpy);
	cpy->map = (char **)malloc(sizeof(char *) * (org->ydim + 1));
	if (cpy->map == 0)
		ft_clearcopy(1, cpy, org);
	cpy->map[org->ydim] = NULL;
	cpy->ydim = 0;
	while (org->map[cpy->ydim] != NULL)
	{
		cpy->x = ft_linelen(org->map[cpy->ydim], '\0');
		cpy->map[cpy->ydim] = (char *)malloc(sizeof(char) * (cpy->x + 1));
		if (cpy->map[cpy->ydim] == 0)
			ft_clearcopy(1, cpy, org);
		cpy->x = 0;
		while (org->map[cpy->ydim][cpy->x] != '\0')
		{
			cpy->map[cpy->ydim][cpy->x] = org->map[cpy->ydim][cpy->x];
			(cpy->x)++;
		}
		(cpy->ydim)++;
	}
}

void	ft_floodfill(t_mapinfo *ffm, int x, int y)
{
	if (y == 0 || (y + 1) == ffm->ydim || x == 0 || ffm->map[y][x + 1] == '\0'\
	|| ffm->noerror == 0 || ffm->map[y][x] == ' ' || ffm->map[y][x] == '\0')
	{
		ffm->noerror = 0;
		return ;
	}
	if (ffm->map[y][x] == '2')
		(ffm->spriteno)++;
	ffm->map[y][x] = 'x';
	if (ft_charinset(ffm->map[y - 1][x], "02 "))
		ft_floodfill(ffm, x, y - 1);
	if (ft_charinset(ffm->map[y - 1][x + 1], "02 "))
		ft_floodfill(ffm, x + 1, y - 1);
	if (ft_charinset(ffm->map[y][x + 1], "02 "))
		ft_floodfill(ffm, x + 1, y);
	if (ft_charinset(ffm->map[y + 1][x + 1], "02 "))
		ft_floodfill(ffm, x + 1, y + 1);
	if (ft_charinset(ffm->map[y + 1][x], "02 "))
		ft_floodfill(ffm, x, y + 1);
	if (ft_charinset(ffm->map[y + 1][x - 1], "02 "))
		ft_floodfill(ffm, x - 1, y + 1);
	if (ft_charinset(ffm->map[y][x - 1], "02 "))
		ft_floodfill(ffm, x - 1, y);
	if (ft_charinset(ffm->map[y - 1][x - 1], "02 "))
		ft_floodfill(ffm, x - 1, y - 1);
}
