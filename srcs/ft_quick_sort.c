/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/28 14:52:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	isolate_sub_lst(t_stacks *stacks, char **operations, int *first)
{
//	printf("------ ISOLATE -------\n");
	while (stacks->a_pile->p && stacks->a_pile->nb != *first)
	{
		if (append_actions("ra", stacks, operations))
			return (1);
	}
	while (!(stacks->a_pile->p))
	{
		if (append_actions("pb", stacks, operations))
			return (1);
	}
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("----ISOLATE DONE-----\n");
//	getchar();
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, char **operations, t_pile **sorted)
{
	int	*first;
	int end;

	first = NULL;
	end = ft_lstlen(stacks->a_pile) > SUBLST_SIZE ? 0 : 1;
//	printf("------ INIT ------\n");
	if (sort_sub_lst(stacks, operations, *sorted, 0))
		return (1);
//	printf("------ INIT DONE ------\n");
	while (!end)
	{
		while (stacks->b_pile)
			if (sort_sub_lst(stacks, operations, *sorted, 1))
				return (1);
		if (!first)
		{
			if (!(first = (int*)malloc(sizeof(int))))
				return(1);
			*first = stacks->a_pile->nb; 
			if (append_actions("ra", stacks, operations))
				return (1);
		}
		if (isolate_sub_lst(stacks, operations, first))
			return (1);
		if (first && stacks->a_pile->nb == *first && !(stacks->b_pile))
			end = 1;
	}
	if (!*sorted)
		*sorted = stacks->a_pile;
	return (0);
}
