/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error_checker.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 21:48:11 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/14 17:47:49 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	ft_prelimcheck(int argc, char *mapfile, t_mapinfo *m)
{
	if (argc < 2)
		errno = 22;
	if (argc < 2)
		perror("Error\nNo map file provided");
	else if (argc > 2)
	{
		errno = 7;
		perror("Error\nToo many arguments provided");
	}
	else if (read(m->fd, 0, 0) == -1)
	{
		errno = 9;
		perror("Error\nCan't read file, check permissions & if it exists");
	}
	else if (ft_checkcub(mapfile))
	{
		errno = 79;
		perror("Error\nFile has wrong extension type, should be .cub");
	}
	else
		return (0);
	ft_quit(1, m);
	return (1);
}

int	ft_checkcub(char *mapfile)
{
	int i;

	i = 0;
	while (mapfile[i] != '\0')
		i++;
	if (mapfile[i - 4] == '.' && mapfile[i - 3] == 'c' && \
	mapfile[i - 2] == 'u' && mapfile[i - 1] == 'b')
		return (0);
	else
		return (1);
}

int	ft_parserror(int type, t_mapinfo *m)
{
	if (type == 1)
	{
		errno = 79;
		perror("Error\nProblem encountered with map elements, they \
may be missing, repeated, contain garbage data or be misplaced");
	}
	else if (type == 2) //COMM Check still needs to be written
	{
		errno = 79;
		perror("Error\nOne or more map elements contain invalid data");
	}
	else if (type == 3) //COMM Check still needs to be written
	{
		errno = 79;
		perror("Error\nThe map provided is invalid, and can cause \
a player to go out of bounds");
	}
	ft_quit(1, m);
	return (1);
}
