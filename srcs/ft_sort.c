/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 13:31:23 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/17 17:11:51 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_bibubblesort(char **tosort)
{
	int items;
	int i;
	int done;
	int holdvalue;
	int dir;
	int counter;
	int change;
	int lchg;
	int schg;

	items = 0;
	while ((*tosort)[items] != '\0')
		items++;
	printf("items: %d\n", items);
	i = 0;
	done = 0;
	counter = 0;
	change = 0;
	printf("%d)	string: %s\n", counter, (*tosort));
	dir = 1;
	schg = items - 1;
	lchg = 0;
	while (!done)
	{
		if ((dir == -1 && i == lchg) || (dir == 1 && i == schg))
		{
			dir = dir * -1;
			lchg = (i == lchg) ? lchg + dir : lchg;
			schg = (i == schg) ? schg + dir : schg;
			i = i + dir;
		}
		printf("	comparing: '%c'[%d] to '%c'[%d] next	(comparing values between %d and %d)\n", (*tosort)[i], i, (*tosort)[i + dir], i + dir, lchg, schg);
		if ((*tosort)[i] * dir >= (*tosort)[i + dir] * dir)
			i = i + dir;
		else
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = holdvalue;
			i = i + dir;
			change = 0;
		}
		change++;
		counter++;
	//	if ((schg - lchg) < items / 2)
		if (change >= (schg - lchg))
			done = 1;
		printf("%d)	string: %s", counter, (*tosort));
	}
	return (items);
}

int	ft_actualbubblesort(char **tosort)
{
	int items;
	int i;
	int done;
	int holdvalue;
	int counter;
	int change;
	int schg;

	items = 0;
	while ((*tosort)[items] != '\0')
		items++;
	printf("items: %d\n", items);
	i = 0;
	done = 0;
	counter = 0;
	change = 0;
	printf("%d)	string: %s\n", counter, (*tosort));
	schg = items - 1;
	while (!done)
	{
		if (i == schg)
		{
			schg--;
			i = 0;
		}
		printf("	comparing: '%c'[%d] to '%c'[%d] next	(comparing values between %d and %d)\n", (*tosort)[i], i, (*tosort)[i + 1], i + 1, 0, schg);
		if ((*tosort)[i] >= (*tosort)[i + 1])
			i++;
		else
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + 1];
			(*tosort)[i + 1] = holdvalue;
			i = i + 1;
			change = 0;
		}
		change++;
		counter++;
	//	if ((schg - lchg) < items / 2)
		if (change > schg)
			done = 1;
		printf("%d)	string: %s", counter, (*tosort));
	}
	return (items);
}

int	main(int argc, char **argv)
{
	ft_bibubblesort(&argv[1]);
	//ft_actualbubblesort(&argv[1]);
	return (0);
}
