/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sorting_algos.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/22 17:25:55 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/23 21:34:10 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_fullbubblesort(char **tosort, int last);
void ft_twowaybbs(char **tosort, int first, int last, char val);
int	ft_originaltwowaybbs(char **tosort, int first, int last, char val);
int	ft_mergesort(char **tosort, int first, int last);

int	main(int argc, char **argv)
{
	int last; //index of last item in set that needs sorting
	int ret;

	last = 0;
	while (argv[1][last] != '\0')
		last++;
	last--;

	ret = 0;
	if (argv[2][0] == 'n')
		ret = last - ft_fullbubblesort(&argv[1], last);
	if (argv[2][0] == 't')
		ft_twowaybbs(&argv[1], 0, last, '\0');
	if (argv[2][0] == 'o')
		ret = ft_originaltwowaybbs(&argv[1], 0, last, '\0');
	if (argv[2][0] == 'm')
		ret = last - ft_mergesort(&argv[1], 0, last);
	// if (argv[2][0] == 's')
	// 	ft_singlebubblesort(&argv[1], last);
	// if (argv[2][0] == 'c')
	// 	ft_bibubblecut(&argv[1]);
	printf("%d) string: |%s|\n", ret, argv[1]); //nn
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

	int checks = 0;
	int swaps = 0;
	int passes = 0;
	i = 0;
	checked = 0;
	while (!(checked > last))
	{
		checks++;
		if (i == last)
		{
			last--;
			passes++;
		}
		if (i >= last)
			i = 0;
		if ((*tosort)[i] >= (*tosort)[i + 1])
		{
			i++;
		}
		else
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + 1];
			(*tosort)[i + 1] = holdvalue;
			i = i + 1;
			checked = 0;
			swaps++;
		}
		checked++;
	}
	printf ("Checks: %d, Swaps: %d, Passes: %d\n", checks, swaps, passes);
	return (last);
}

/*
**	Sorts the entire string using a two way bubble sort algorithm,
**	which alternates in pushing the min & max vals to their
**	respective ends of the set, and as such is faster than the regular bbs
**	by 'shortening' the set on two ends and completing in fewer passes.
**
**	Whenever the end of a string is reached, the index jumps to
**	wherever the next swap is needed to be made, meaning fewer
**	checks per pass too.
**	The result is still a fully sorted string from High to Low.
**
**  Optimisations: You could split up the check ternary.
**	It would also be nice to have the function return the number of passes.
**	Because of the Norme line limit I didn't do either of these things.
**
**	int i; // index in set
**	int check; // values consecutively checked without needing to change
**	int dir; //the current direction in which is being sorted (+1 or -1)
*/

void	ft_twowaybbs(char **tosort, int first, int last, char val)
{
	int i;
	int check;
	int dir;

	i = first;
	check = 0;
	dir = 1;
	while (last > first)
	{
		check = ((*tosort)[i] * dir < (*tosort)[i + dir] * dir) ? 0 : check + 1;
		if ((*tosort)[i] * dir < (*tosort)[i + dir] * dir)
		{
			val = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = val;
		}
		i = i + dir;
		if ((dir == -1 && i == first) || (dir == 1 && i == last))
		{
			dir = dir * -1;
			i = i + (check + 1) * dir;
			first = (dir == 1) ? i : first;
			last = (dir == -1) ? i : last;
		}
	}
}

// Visualiser (put in if-statement for when end is reached):
//
// if (dir == -1)
// {
// for (int j = 0; (*tosort)[j] != '\0'; j++)
// {
// 	printf("\033[0m");
// 	if (j == first || j == last)
// 		printf("\033[0;31m");
// 	if (j == i)
// 		printf("\033[0;34m");
// 	printf("%c", (*tosort)[j]);
// }
// printf("|\n");
// }

int	ft_originaltwowaybbs(char **tosort, int first, int last, char val)
{
	int i;
	int check;
	int dir;

	int passes = 0;
	int checks = 0;
	int swaps = 0;
	i = first;
	check = 0;
	dir = 1;
	while (last > first)
	{
		checks++;
		check = ((*tosort)[i] * dir < (*tosort)[i + dir] * dir) ? 0 : check + 1;
		if ((*tosort)[i] * dir < (*tosort)[i + dir] * dir)
		{
			val = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = val;
			swaps++;
		}
		i = i + dir;
		if ((dir == -1 && i == first) || (dir == 1 && i == last))
		{
			passes++;
			dir = dir * -1;
			i = i + (check + 1) * dir;
			first = (dir == 1) ? i : first;
			last = (dir == -1) ? i : last;
				// if (dir == -1 || 1)
				// {
				// for (int j = 0; (*tosort)[j] != '\0'; j++)
				// {
				// 	printf("\033[0m");
				// 	if (j == first || j == last)
				// 		printf("\033[0;31m");
				// 	if (j == i)
				// 		printf("\033[0;34m");
				// 	printf("%c", (*tosort)[j]);
				// }
				// printf("|\n");
				// }
		}
	}
	printf ("%s|\n", (*tosort));
	printf ("Checks: %d, Swaps: %d, Passes: %d\n", checks, swaps, passes);
	return (first);
}

// int	ft_mergesort(char **tosort, int first, int last)
// {
// 	int mid;

// 	printf("merge sort: %d, %d\n", first, last);
// 	if ((last - first) < 2)
// 		ft_originaltwowaybbs(tosort, first, last, 'a');
// 	else
// 	{
// 		mid = ((last - first) / 2) + first;
// 		ft_mergesort(tosort, first, mid);
// 		ft_mergesort(tosort, mid + 1, last);
// 	}
// 	return (0);
// }

int ft_merge(char **tosort, int first, int mid, int last);

int	ft_mergesort(char **tosort, int first, int last)
{
	int mid;

	//printf("merge sort: %d, %d\n", first, last);
	if (last > first)
	{
		mid = ((last - first) / 2) + first;
		ft_mergesort(tosort, first, mid);
		ft_mergesort(tosort, mid + 1, last);
		ft_merge(tosort, first, mid, last);
	}
	return (0);
}

int ft_merge(char **tosort, int first, int mid, int last)
{
	int		i;
	int		l;
	int		r;
	char	val;

	printf("|%s|\n", (*tosort));
	i = first;
	l = first;
	r = mid + 1;
	while (i != last)
	{
		while ((*tosort)[i] < (*tosort)[r] && i != last)
		{
			val = (*tosort)[i];
			(*tosort)[i] = (*tosort)[r];
			(*tosort)[r] = val;
			i++;
			if ((*tosort)[r] < (*tosort)[r + 1] && r != last)
				r++;
			else if ((*tosort)[r] > (*tosort)[r - 1] && r != mid + 1)
				r--;
		}
		while ((*tosort)[i] >= (*tosort)[r] && i != last)
			i++;
	}
	printf("Sorting %d-(%d)-%d: |",first, mid + 1, last);
	for (int k = first; k != last + 1; k++)
	{
		if (k > 0 && (*tosort)[k] > (*tosort)[k - 1])
			printf("\033[0;31m");
		if (k == r)
			printf("\033[0;34m");
		printf("%c", (*tosort)[k]);
		printf("\033[0m");
	}
	printf("|\n");
}
