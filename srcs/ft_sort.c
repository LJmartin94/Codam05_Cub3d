/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sort.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: lindsay <lindsay@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/17 13:31:23 by lindsay       #+#    #+#                 */
/*   Updated: 2020/09/22 17:13:19 by lindsay       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_cutthedeck(char **tosort, int len);
int	ft_shufflethedeck(char **tosort, int len);
int	ft_bibubblecut(char **tosort);
int	ft_bbbs(char **tosort, int first, int last);
int ft_mergesort(char **tosort, int first, int last);

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

int	ft_shufflethedeck(char **tosort, int len)
{
	long ahalf;
	long bhalf;
	int i;
	int hold;

	ahalf = 0;
	bhalf = 0;
	i = 0;
	while (i < (len / 2))
	{
		ahalf = ahalf + (*tosort)[i];
		i++;
	}
	if ((len % 2) == 1)
		i++;
	while (i < len)
	{
		bhalf = bhalf + (*tosort)[i];
		i++;
	}
	printf(" ahalf:	%ld	bhalf:	%ld	", ahalf, bhalf);
	if (ahalf >= bhalf)
		return (0);
	printf("\n GUNNA SHUFFLE !!! \n");
	i = 0;
	while (i < (len / 2))
	{
		hold = (*tosort)[i];
		(*tosort)[i] = (*tosort)[len - 1 - i];
		(*tosort)[len - 1 - i] = hold;
		i++;
	}
	return (1);
}

int	ft_cutthedeck(char **tosort, int len)
{
	long ahalf;
	long bhalf;
	int i;
	int hold;

	ahalf = 0;
	bhalf = 0;
	i = 0;
	while (i < (len / 2))
	{
		ahalf = ahalf + (*tosort)[i];
		i++;
	}
	if ((len % 2) == 1)
		i++;
	while (i < len)
	{
		bhalf = bhalf + (*tosort)[i];
		i++;
	}
	printf(" ahalf:	%ld	bhalf:	%ld	", ahalf, bhalf);
	if (ahalf >= bhalf)
		return (0);
	printf("\n GUNNA CUT !!! \n");
	i = 0;
	while (i < (len / 2))
	{
		hold = (*tosort)[i];
		(*tosort)[i] = (*tosort)[((len + 1) / 2) + i];
		(*tosort)[((len + 1) / 2) + i] = hold;
		i++;
	}
	return (1);
}

// int	ft_cutsort(char **tosort)
// {
// 	int items; // the amount of individual items in the set
// 	int parts; // the amount of parts the original set is broken up into
// 	int	thispart; // the number of the part you're in
// 	int	sizeofpart; // the amount of individual elements in the part
// 	int	nextpartstart; // the index of the string the next part starts
// 	int i; //index in the string
// 	int j;
// 	int done;
// 	int holdvalue;
// 	int counter;
// 	int change;

// 	items = 0;
// 	i = 0;
// 	while ((*tosort)[items] != '\0') //get number of items plus push highest value out
// 	{
// 		if ((*tosort)[i] < (*tosort)[i + 1] && (*tosort)[i + 1] != '\0')
// 		{
// 			holdvalue = (*tosort)[i];
// 			(*tosort)[i] = (*tosort)[i + 1];
// 			(*tosort)[i + 1] = holdvalue;
// 		}
// 		items++;
// 	}
// 	if (items % 2 == 1)
// 		items--;
// 	//15 becomes 14 in our example.
// 	// 14 / 2 = 7, 7 % 2 = 1, so 
// 	printf("items: %d\n", items);
// 	done = 0;
// 	counter = 0;
// 	change = 0;
// 	printf("%d)	string: %s\n", counter, (*tosort));
// 	parts = 1;
// 	thispart = 0;
// 	while (!done)
// 	{
// 		parts = parts * 2;
// 		sizeofpart = (items + parts - 1) / parts;
// 		while (thispart + 1 < parts)
// 		{
// 			i = 0;
// 			while (i < sizeofpart)
// 			{
// 				holdvalue = (*tosort)[i + (thispart)];
// 				(*tosort)[i] = (*tosort)[i + 1];
// 				(*tosort)[i + 1] = holdvalue;
// 			}
// 		}
// 	}
	
	
	
	
	
// 	while (!done)
// 	{
// 		if (i == schg)
// 		{
// 			schg--;
// 			i = 0;
// 		}
// 		printf("	comparing: '%c'[%d] to '%c'[%d] next	(comparing values between %d and %d)\n", (*tosort)[i], i, (*tosort)[i + 1], i + 1, 0, schg);
// 		if ((*tosort)[i] >= (*tosort)[i + 1])
// 			i++;
// 		else
// 		{
// 			holdvalue = (*tosort)[i];
// 			(*tosort)[i] = (*tosort)[i + 1];
// 			(*tosort)[i + 1] = holdvalue;
// 			i = i + 1;
// 			change = 0;
// 		}
// 		change++;
// 		counter++;
// 	//	if ((schg - lchg) < items / 2)
// 		if (change > schg)
// 			done = 1;
// 		printf("%d)	string: %s", counter, (*tosort));
// 	}
// 	return (items);
// }


int	main(int argc, char **argv)
{
	int last;

	last = 0;
	while (argv[1][last] != '\0')
		last++;
	if (argv[2][0] == 'b')
		ft_bibubblesort(&argv[1]);
	if (argv[2][0] == 'n')
		ft_actualbubblesort(&argv[1]);
	if (argv[2][0] == 'c')
		ft_bibubblecut(&argv[1]);
	if (argv[2][0] == 'm')
		ft_mergesort(&argv[1], 0, last - 1);
	// 	ft_cutsort(&argv[1]);
	return (0);
}

int	ft_bbbsthis(char **tosort, int *first, int *last);
int	ft_partcompare(char **tosort, int *first, int *last, int parts);

int	ft_bibubblecut(char **tosort)
{
	int items;
	int first;
	int last;
	int parts;
	int changes = 0; //superfluous

	items = 0;
	while ((*tosort)[items] != '\0')
		items++;
	last = items - 1;
	first = 0;
	changes = changes + ft_bbbsthis(tosort, &first, &last); //superfluous
	parts = 1;
	for(int i = 0; i < 10; i++) //need to figure out stopping condition
	{
		parts = parts * 2;
		changes = changes + ft_partcompare(tosort, &first, &last, parts);
	}
	printf("\n%d)	string: %s\n", changes, (*tosort));
	printf("items: %d\n", items);
}

int	ft_partcompare(char **tosort, int *first, int *last, int parts)
{
	int items = (*last - *first + 1);
	int partsize;
	long ahalf;
	long bhalf;
	int i;
	int hold;
	int done;

	done = 0;
	while (!done)
	{
		parts = parts * 2;
		partsize = (items / parts) + (items % parts) / (parts / 2);
		ahalf = 0;
		bhalf = 0;
		i = ((items - 1) / 2) - partsize;
		while (i <= ((items - 1) / 2))
		{
			ahalf = ahalf + (*tosort)[i];
			i++;
		}
		if ((items % 2) == 1)
			i--;
		while (i < ((items - 1) / 2) + partsize)
		{
			bhalf = bhalf + (*tosort)[i];
			i++;
		}
		printf(" ahalf:	%ld	bhalf:	%ld	", ahalf, bhalf);
		if (ahalf > bhalf || partsize <= 1)
			done = 1;
	}
	if (ahalf == bhalf)
		return (0);
	printf("\n GUNNA CUT !!! \n");
	i = ((items - 1) / 2) - partsize;
	while (i <= ((items - 1) / 2))
	{
		hold = (*tosort)[i];
		(*tosort)[i] = (*tosort)[((items + 1) / 2) + i];
		(*tosort)[((items + 1) / 2) + i] = hold;
		i++;
	}
	printf("string: %s\n", (*tosort));
	return (1);
}

int	ft_bbbsthis(char **tosort, int *first, int *last)
{
	int i;
	int done;
	int holdvalue;
	int dir;
	int counter = 0;
	int change;

	i = 0;
	done = 0;
	change = 0;
	printf("%d)	string: %s\n", counter, (*tosort));
	dir = 1;
	while (!done || i != 0)
	{
		if ((dir == -1 && i == *first) || (dir == 1 && i == *last))
		{
			done = 1;
			dir = dir * -1;
			*first = (i == *first) ? *first + dir : *first;
			*last = (i == *last) ? *last + dir : *last;
			i = i + dir;
		}
		printf("	comparing: '%c'[%d] to '%c'[%d] next	(comparing values between %d and %d)\n", (*tosort)[i], i, (*tosort)[i + dir], i + dir, *first, *last);
		if ((*tosort)[i] * dir < (*tosort)[i + dir] * dir)
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = holdvalue;
			change++;
		}
		i = i + dir;
		counter++;
		printf("%d)	string: %s", counter, (*tosort));
	}
	return (change);
}

int ft_mergesort(char **tosort, int first, int last)
{
	int mid;

	printf("merge sort: %d, %d\n", first, last);
	if ((last - first) <= 2)
		ft_bbbs(tosort, first, last);
	else
	{
		mid = ((last - first) / 2) + first;
		ft_mergesort(tosort, first, mid);
		ft_mergesort(tosort, mid + 1, last);
	}
	return (0);
}

int	ft_bbbs(char **tosort, int first, int last)
{
	int i;
	int done;
	int holdvalue;
	int dir;
	int counter = 0;
	int change;

	i = first;
	done = 0;
	change = 0;
	printf("%d)	string: %s\n", counter, (*tosort));
	dir = 1;
	while (!done || i != first)
	{
	//printf("|%d, %d|\n", i, last);
		if ((dir == -1 && i == first) || (dir == 1 && i == last))
		{
			done = 1;
			dir = dir * -1;
			first = (i == first) ? first + dir : first;
			last = (i == last) ? last + dir : last;
			i = i + dir;
		}
		//printf("	comparing: '%c'[%d] to '%c'[%d] next	(comparing values between %d and %d)\n", (*tosort)[i], i, (*tosort)[i + dir], i + dir, first, last);
		if ((*tosort)[i] * dir < (*tosort)[i + dir] * dir)
		{
			holdvalue = (*tosort)[i];
			(*tosort)[i] = (*tosort)[i + dir];
			(*tosort)[i + dir] = holdvalue;
			change++;
		}
		i = i + dir;
		counter++;
		//printf("%d)	string: %s", counter, (*tosort));
	}
	return (change);
}
