/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublist_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:48:45 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/22 11:36:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	three_sort(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	char	*actions;

	printf("--------THREE SORT-------\n");
	actions = "";
	if (stacks->b_pile->nb > stacks->b_pile->next->nb &&\
			stacks->b_pile->nb > stacks->b_pile->next->next->nb)
	{
		if (stacks->b_pile->next->nb < stacks->b_pile->next->next->nb)
			actions = "pa\nsb\npb";
	}
	else if (stacks->b_pile->nb < stacks->b_pile->next->nb &&\
			stacks->b_pile->nb < stacks->b_pile->next->next->nb)
	{
		if (stacks->b_pile->next->nb < stacks->b_pile->next->next->nb)
			actions = "rb\nsb";
		else
			actions = "rb";
	}
	else
	{
		if (stacks->b_pile->next->nb < stacks->b_pile->next->next->nb)
			actions = "rrb";
		else
			actions = "sb";
	}
	printf("actions : %s", actions);
	if (*actions && append_actions(actions, stacks, operations, fcts_tab))
		return (1);
	while (stacks->b_pile)
	{
		stacks->b_pile->p = 1;
		if (append_actions("pa", stacks, operations, fcts_tab))
			return (1);
	}
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----THREE SORT DONE-----\n");
	return (0);
}

static int	one_two_sort(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	int len;

	len = ft_lstlen(stacks->b_pile);
	printf("----ONE TWO SORT-----\n");
	if (len == 2)
		if (stacks->b_pile->nb < stacks->b_pile->next->nb)
			if (append_actions("sb", stacks, operations, fcts_tab))
				return (1);
	while (stacks->b_pile)
	{
		stacks->b_pile->p = 1;
		if (append_actions("pa", stacks, operations, fcts_tab))
			return (1);
	}
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----ONE TWO SORT DONE-----\n");
	return (0);
}


int	little_list_sort(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	int len;
	int pos;
	int	max;
	t_pile	*current;
	int	i;

	len = ft_lstlen(stacks->b_pile);
	i = len;
	while (--i >= 3)
	{
		printf("-----SELECTION SORT------\n");
		current = stacks->b_pile;
		max = current->nb;
		while (current)
		{
			if (current->nb > max)
				max = current->nb;
			current = current->next;
		}
//		ft_putlst(stacks->a_pile);
		pos = ft_lstgetpos(stacks->b_pile, max);
//		printf("min : %d\npos : %d\n", min, pos);
		if (pos <= len / 2)
		{
			while (pos--)
				if (append_actions("rb", stacks, operations, fcts_tab))
					return (1);
		}
		else
			while (++pos <= len)
				if (append_actions("rrb", stacks, operations, fcts_tab))
					return (1);
		stacks->b_pile->p = 1;
		if (append_actions("pa", stacks, operations, fcts_tab))
			return (1);
		len--;
		ft_putlst(stacks->a_pile);
		ft_putlst(stacks->b_pile);
		getchar();
		printf("----SELECTION SORT DONE-----\n");
	}
	if (i == 2)
		return (three_sort(stacks, operations, fcts_tab));
	else
		return (one_two_sort(stacks, operations, fcts_tab));
	return (0);
}
