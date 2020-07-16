/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 21:37:34 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/16 16:41:19 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		get_next_line(t_mapinfo *m, char **line)
{
	static char	remainder[BUFFER_SIZE + 1];
	int			i;
	int			nl;
	int			red;

	if (line == NULL || m->fd < 0 || BUFFER_SIZE < 0)
		xt_quit(-1, m);
	*line = (char *)malloc(sizeof(char) * (1));
	if (*line == 0)
		return (xt_gnlerror(remainder, line, m));
	i = 0;
	nl = 1;
	while (nl)
	{
		if (remainder[0] == '\0')
			red = ft_fill_remainder(remainder, m->fd, &nl);
		if (red == -1)
			return (xt_gnlerror(remainder, line, m));
		if (!(ft_malloc_expander(line, i, ft_linelen(remainder, '\n'))))
			return (xt_gnlerror(remainder, line, m));
		if (remainder[0] != '\0')
			red = ft_handle_remainder(line, remainder, &i, &nl);
	}
	return (red);
}

int		ft_fill_remainder(char *remainder, int fd, int *nl)
{
	int		red;

	red = read(fd, remainder, BUFFER_SIZE);
	if (red <= 0)
		*nl = 0;
	return (red);
}

int		ft_handle_remainder(char **line, char *rmn, int *i, int *nl)
{
	int	j;

	j = 0;
	while (rmn[j] != '\n' && rmn[j] != '\0')
	{
		(*line)[*i] = rmn[j];
		*i = *i + 1;
		j++;
	}
	(*line)[*i] = '\0';
	if (rmn[j] == '\n')
		*nl = 0;
	ft_clear_remainder(rmn, j);
	return (1);
}

void	ft_clear_remainder(char *remainder, int j)
{
	int	k;

	k = 0;
	while (remainder[j] != '\0')
	{
		j++;
		remainder[k] = remainder[j];
		k++;
	}
	while (k < j)
	{
		remainder[k] = '\0';
		k++;
	}
}

int		xt_gnlerror(char *remainder, char **line, t_mapinfo *m)
{
	int i;

	i = 0;
	while (i < (BUFFER_SIZE + 1))
	{
		remainder[i] = '\0';
		i++;
	}
	if (!(*line == 0))
		free(*line);
	*line = NULL;
	xt_mallocerror(m);
	return (-1);
}
