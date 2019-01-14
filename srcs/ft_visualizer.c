/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:56:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/14 16:52:53 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	find_max(t_pile *a_pile, t_pile *b_pile)
{
	t_pile *current;
	int		int_max;

	current = a_pile;
	int_max = 0;
	while (current)
	{
		if (current->nb > int_max)
			int_max = current->nb;
		current = current->next;
	}
	current = b_pile;
	while (current)
	{
		if (current->nb > int_max)
			int_max = current->nb;
		current = current->next;
	}
	return (int_max);
}
/*
static void	determine_values(int (*len)[2], t_pile *(*current)[2],\
		int (*values)[2])
{
	*(values[0]) = 0;
	*(values[1]) = 0;
//	printf("determine values : %d | %d\n", *(values[0]), *(values[1]));
	printf("len : %d | %d\n", *(len[0]), *(len[1]));
	if (*(len[0]) >= *(len[1]))
	{
		printf("%d\n", (*(current[0]))->nb);
		*(values[0]) = (*(current[0]))->nb;
		printf("a\n");
		if (*(len[1]) >= *(len[0]))
		{
			printf("b\n");
			*(values[1]) = (*(current[1]))->nb;
			*(len[1]) -= 1;
			*(current[1]) = (*(current[1]))->next;
		}
		*(len[0]) -= 1;
		*(current[0]) = (*(current[0]))->next;
	}
	else
	{
		printf("b\n");
		*(values[1]) = (*(current[1]))->nb;
		*(len[1]) -= 1;
		*(current[1]) = (*(current[1]))->next;
	}
//	printf("determine values : %d | %d\n", *(values[0]), *(values[1]));
}
*/
static void	determine_values(int (*len)[2], t_pile *(*current)[2],\
		int (*values)[2])
{
	*(values[0]) = 0;
	*(values[1]) = 0;
//	printf("determine values : %d | %d\n", *(values[0]), *(values[1]));
	printf("len : %d | %d\n", *(len[0]), *(len[1]));
	if (*(len[0]) >= *(len[1]))
	{
		printf("%d\n", (*(current[0]))->nb);
		*(values[0]) = (*(current[0]))->nb;
		printf("a\n");
		if (*(len[1]) >= *(len[0]))
		{
			printf("b\n");
			*(values[1]) = (*(current[1]))->nb;
			*(len[1]) -= 1;
			*(current[1]) = (*(current[1]))->next;
		}
		*(len[0]) -= 1;
		*(current[0]) = (*(current[0]))->next;
	}
	else
	{
		printf("b\n");
		*(values[1]) = (*(current[1]))->nb;
		*(len[1]) -= 1;
		*(current[1]) = (*(current[1]))->next;
	}
//	printf("determine values : %d | %d\n", *(values[0]), *(values[1]));
}

static int	display_values(int values[2], int int_max)
{
	char	*a_values;
	char	*b_values;

	if (!(a_values = (char*)malloc(values[0] + 1)) ||\
				!(b_values = (char*)malloc(values[1] + 1)))
		return (1);
	a_values = ft_memset(a_values, '|', values[0]);
	b_values = ft_memset(b_values, '|', values[1]);
	printf("%*s  %*s\n", int_max, a_values, int_max, b_values);
	return (0);
}

int			visualizer(t_pile *a_pile, t_pile *b_pile)
{
	int		int_max;
	t_pile	*a_current;
	t_pile	*b_current;
	int		len;
	int		value;

	int_max = find_max(a_pile, b_pile);
	len[0] = ft_lstlen(a_pile);
	len[1] = ft_lstlen(b_pile);
	a_current = a_pile;
	b_current = b_pile;
	sleep(1);
	system("clear");
	printf("len : %d | %d\n", len[0], len[1]);
	while (a_current || b_current)
	{
		determine_values(&len, &current, &values);
		printf("values : %d | %d\n", values[0], values[1]);
		if (display_values(values, int_max))
			return (1);
	}
	return (1);
}
/*
int			visualizer(t_pile *a_pile, t_pile *b_pile)
{
	int		int_max;
	t_pile	*(current[2]);
	int		len[2];
	int		values[2];

	int_max = find_max(a_pile, b_pile);
	len[0] = ft_lstlen(a_pile);
	len[1] = ft_lstlen(b_pile);
	current[0] = a_pile;
	current[1] = b_pile;
	sleep(1);
	system("clear");
	printf("len : %d | %d\n", len[0], len[1]);
	while ((current[0]))
	{
		determine_values(&len, &current, &values);
		printf("values : %d | %d\n", values[0], values[1]);
		if (display_values(values, int_max))
			return (1);
	}
	return (1);
}
*/
