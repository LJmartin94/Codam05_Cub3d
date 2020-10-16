/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_floodfill.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/16 11:16:07 by lindsay       #+#    #+#                 */
/*   Updated: 2020/10/16 11:19:18 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	ft_floodfill(t_mapinfo *ffm, int x, int y)
{
	if (ft_checkflooderror(ffm, x, y))
		return ;
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

int		ft_checkflooderror(t_mapinfo *ffm, int x, int y)
{
	int up;
	int down;

	if (y == 0 || (y + 1) == ffm->ydim || x == 0 || ffm->map[y][x + 1] == '\0'\
	|| ffm->noerror == 0 || ffm->map[y][x] == ' ' || ffm->map[y][x] == '\0')
	{
		ffm->noerror = 0;
		return (1);
	}
	up = ft_linelen(ffm->map[y - 1], '\0');
	down = ft_linelen(ffm->map[y + 1], '\0');
	if (x > up || x > down)
	{
		ffm->noerror = 0;
		return (1);
	}
	return (0);
}
