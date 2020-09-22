/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sorting_algos.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 17:25:55 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/22 18:57:39 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_fullbubblesort(char **tosort, int last);
int	ft_twowaybbs(char **tosort, int first, int last);

int	main(int argc, char **argv)
{
	int last; //index of last item in set that needs sorting
	int ret;

	last = 0;
	while (argv[1][last] != '\0')
		last++;
	last--;
	
	if (argv[2][0] == 'n')
		ret = last - ft_fullbubblesort(&argv[1], last);
	if (argv[2][0] == 't')
		ret = last - ft_twowaybbs(&argv[1], 0, last);
	// if (argv[2][0] == 's')
	// 	ft_singlebubblesort(&argv[1], last);
	// if (argv[2][0] == 'c')
	// 	ft_bibubblecut(&argv[1]);
	// if (argv[2][0] == 'm')
	// 	ft_mergesort(&argv[1], 0, last - 1);
	printf("%d) string: |%s|", ret, argv[1]); //nn
	return (0);
}

/*
**	Sorts the entire string using the normal bubble sort algorithm,
**	result is a fully sorted string from High to Low.
**
**	Return value is the last index that needed sorting,
**	such that the original parameter 'last' minus ret 'last' is the
**	number of times the set was looped through.
**
**	int i; // index in set
**	int holdvalue; // original value of index being swapped over
**	int checked; // values consecutively checked without needing to change
**
**	Remove the "checked = 0;" line in the else block for a single iteration.
*/

int	ft_fullbubblesort(char **tosort, int last)
{
	int i;
	int holdvalue;
	int checked;

	i = 0;
	checked = 0;
	while (!(checked > last))
	{
		if (i == last)
			last--;
		if (i >= last)
			i = 0;
		if ((*tosort)[i] >= (*tosort)[i + 1])
			i++;
		else
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + 1];
			(*tosort)[i + 1] = holdvalue;
			i = i + 1;
			checked = 0;
		}
		checked++;
	}
	return (last);
}

/*
**	Sorts the entire string using a two way bubble sort algorithm,
**	which alternates in pushing the min & max vals to their
**	respective ends of the set, and as such is slightly
**	faster by 'shortening' the set on two ends.
**	The result is still a fully sorted string from High to Low.
**
**	Return value is the 'length of the middle', i.e. how many items were
**	in between min & max when the string was fully sorted,
**
**	int i; // index in set
**	int holdvalue; // original value of index being swapped over
**	int checked; // values consecutively checked without needing to change
*/

int	ft_twowaybbs(char **tosort, int first, int last)
{
	int i;
	int holdvalue;
	int checked;
	int dir;

	i = 0;
	checked = 0;
	dir = 1;
	while (!(checked > (last - first) )) //condition hasnt been correctly translated yet
	{
		if ((dir == -1 && i == first) || (dir == 1 && i == last))
		{
			dir = dir * -1;
			first = (i == first) ? first + dir : first;
			last = (i == last) ? last + dir : last;
			i = i + dir;
		}
		checked++;
		if ((*tosort)[i] * dir < (*tosort)[i + dir] * dir)
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = holdvalue;
			checked = 0;
		}
		i = i + dir;
	}
	return (last - first);
}
