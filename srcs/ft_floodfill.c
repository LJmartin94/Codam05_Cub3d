/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_floodfill.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 13:33:27 by lindsay       #+#    #+#                 */
/*   Updated: 2020/07/16 16:35:26 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_floodfill(t_mapinfo *ffm, int x, int y)
{
	if (y == 0 || (y + 1) == ffm->ydim || x == 0 || ffm->map[y][x + 1] == '\0'\
	|| ffm->noerror == 0 || ffm->map[y][x] == ' ' || ffm->map[y][x] == '\0')
	{
		ffm->noerror = 0;
		return (1);
	}
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
	return (0);
}
	//map is bounded by y[0] && y[x] = '\0' on the x axis, by [0]x and [ydims]x on the y axis.
