/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublist_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:48:45 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/23 16:41:43 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	three_sort(t_stacks *stacks, char **operations, int index)
{
	char	*actions;
	t_pile	*pile;

	printf("--------THREE SORT-------\n");
	actions = "";
	pile = index ? stacks->b_pile : stacks->a_pile;
	if (pile->nb > pile->next->nb &&\
			pile->nb > pile->next->next->nb)
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "pa\nsb\npb" : "pb\nsa\npa";
	}
	else if (pile->nb < pile->next->nb &&\
			pile->nb < pile->next->next->nb)
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "rb\nsb" : "ra\nsa";
		else
			actions = index ? "rb" : "ra";
	}
	else
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "rrb" : "rra";
		else
			actions = index ? "sb" : "sa";
	}
	if (*actions && append_actions(actions, stacks, operations))
		return (1);
	actions = index ? "pa" : "pb";
	pile = index ? stacks->b_pile : stacks->a_pile;
	while (pile)
	{
		pile->p = 1;
		if (append_actions(actions, stacks, operations))
			return (1);
		pile = index ? stacks->b_pile : stacks->a_pile;
	}
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----THREE SORT DONE-----\n");
	return (0);
}

static int	one_two_sort(t_stacks *stacks, char **operations, int index)
{
	int		len;
	t_pile	*pile;
	char	*action;

	pile = index ? stacks->b_pile : stacks->a_pile;
	len = ft_lstlen(pile);
	printf("----ONE TWO SORT-----\n");
	if (len == 2)
		if (pile->nb < pile->next->nb)
		{
			action = index ? "sb" : "sa";
			if (append_actions(action, stacks, operations))
				return (1);
		}
	action = index ? "pa" : "pb";
	while (pile)
	{
		pile = index ? stacks->b_pile : stacks->a_pile;
		pile->p = 1;
		if (append_actions(action, stacks, operations))
			return (1);
	}
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----ONE TWO SORT DONE-----\n");
	return (0);
}

static int	push_max(t_stacks *stacks, char **operations, int index, int max)
{
	int	pos_max;
	char	*action;
	t_pile	*pile;
	int len;

	pile = index ? stacks->b_pile : stacks->a_pile;
	pos_max = ft_lstgetpos(pile, max);
	len = ft_lstlen(pile);
	if (pos_max <= len / 2)
	{
		action = index ? "rb" : "ra";
		while (pos_max--)
			if (append_actions(action, stacks, operations))
				return (1);
	}
	else
	{
		action = index ? "rrb" : "rra";
		while (++pos_max <= len)
			if (append_actions(action, stacks, operations))
				return (1);
	}
	pile = index ? stacks->b_pile : stacks->a_pile;
	pile->p = 1;
	action = index ? "pa" : "pb";
	if (append_actions(action, stacks, operations))
		return (1);
	return (0);
}

int	little_list_sort(t_stacks *stacks, char **operations, int index)
{
	int	max;
	t_pile	*current;
	t_pile	*pile;
	int	i;

	pile = index ? stacks->b_pile : stacks->a_pile;
	i = ft_lstlen(pile);
	while (--i >= 3)
	{
		printf("-----SELECTION SORT------\n");
		pile = index ? stacks->b_pile : stacks->a_pile;
		current = pile;
		max = current->nb;
		while (current)
		{
			if (current->nb > max)
				max = current->nb;
			current = current->next;
		}
		if (push_max(stacks, operations, index, max))
			return (1);
		ft_putlst(stacks->a_pile);
		ft_putlst(stacks->b_pile);
		getchar();
		printf("----SELECTION SORT DONE-----\n");
	}
	if (i == 2)
		return (three_sort(stacks, operations, index));
	else
		return (one_two_sort(stacks, operations, index));
	return (0);
}
