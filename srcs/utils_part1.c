/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_part1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/08 19:03:23 by limartin      #+#    #+#                 */
/*   Updated: 2020/07/09 17:23:53 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		ft_malloc_expander(char **str, int size, int grow)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = (char *)malloc(sizeof(char) * (size + 1));
	if (cpy == 0)
		return (0);
	while (i < size)
	{
		cpy[i] = (*str)[i];
		i++;
	}
	free(*str);
	*str = (char *)malloc(sizeof(char) * (size + grow + 1));
	while ((i > 0) && !(*str == 0))
	{
		i--;
		(*str)[i] = cpy[i];
	}
	free(cpy);
	if (*str == 0)
		return (0);
	(*str)[size + grow] = '\0';
	return (size + grow + 1);
}

size_t	ft_linelen(const char *s, char n)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != n)
		len++;
	return (len);
}

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		j = 0;
		while (haystack[i] == needle[j])
		{
			i++;
			j++;
			if (needle[j] == '\0')
				return ((char *)haystack + i - j);
		}
		if ((j > 0) && !(haystack[i] == needle[j]))
			i = i - j + 1;
		if (j == 0)
			i++;
	}
	return (0);
}
