/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/15 15:31:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	sort_sub_lst(t_pile **a_pile, t_pile **b_pile, char **operations)
{
	t_pile	*pivot;
	char	*action;
	char	*tmp;

	pivot = ft_lstgetlast(*a_pile);
	pivot->p = 1;
	while ((*a_pile))
	{
		if ((*a_pile)->nb > pivot->nb && (*a_pile)->next)
		{
			action = "ra";
			rotate(action, a_pile, b_pile);
		}
		else
		{
			action = "pb";
			push(action, a_pile, b_pile);
		}
		tmp = *operations;
		if (!(*operations = ft_strjoin(*operations, action)))
			return (1);
		free(tmp);
	}
	return (0);
}

static int	isolate_sub_lst(t_pile **a_pile, t_pile **b_pile,\
		char **operations, int *first)
{
	char *tmp;

	while ((*b_pile)->p && (!first || (*b_pile)->nb != *first))
	{
		tmp = *operations;
		if (!(*operations = ft_strjoin(*operations, "rb")))
			return (1);
		free(tmp);
		rotate("rb", a_pile, b_pile);
	}
	while (!((*b_pile)->p))
	{
		tmp = *operations;
		if (!(*operations = ft_strjoin(*operations, "pa")))
			return (1);
		free(tmp);
		rotate("pa", a_pile, b_pile);
	}
	return (0);
}

char		*ft_quick_sort(t_pile **a_pile, t_pile **b_pile)
{
	int		*first;
	char	*operations;
	int		end;

	end = 0;
	if (!(operations = (char*)ft_memalloc(1)))
		return (NULL);
	while (!end)
	{
		while (*a_pile)
			if (sort_sub_lst(a_pile, b_pile, &operations) == 1)
				return (NULL);
		if (!first)
		{
			if (!(first = (int*)malloc(sizeof(int))))
				return(NULL);
			*first = (*b_pile)->nb; 
		}
		if (isolate_sub_lst(a_pile, b_pile, &operations, first) == 1)
			return (NULL);
		if (first && (*b_pile)->nb == *first && !(*a_pile))
			end = 1;
	}
	printf("OK\n");
	return (operations);
}
