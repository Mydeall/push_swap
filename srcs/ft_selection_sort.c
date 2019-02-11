/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublist_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:48:45 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:08:08 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	apply_one_three_sort(t_stacks *stacks, char *actions, int index)
{
	t_pile	*current;
	char	*action;

	if (*actions && append_actions(actions, stacks))
		return (1);
	current = stacks->a_pile;
	while (!index && current)
	{
		current->p = 1;
		current = current->next;
	}
	while ((stacks->rr)[1])
	{
		if (append_actions("ra", stacks))
			return (1);
		(stacks->rr)[1]--;
	}
	while (stacks->b_pile)
	{
		action = index ? "pa\nra" : "pa";
		stacks->b_pile->p = 1;
		if (append_actions(action, stacks))
			return (1);
	}
	return (0);
}

static int	three_sort(t_stacks *stacks, int index)
{
	char	*actions;
	t_pile	*pile;

	pile = index ? stacks->b_pile : stacks->a_pile;
	actions = "";
	if (pile->nb > pile->next->nb && pile->nb > pile->next->next->nb)
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "rb" : "ra";
		else
			actions = index ? "rb\nsb" : "ra\nsa";
	}
	else if (pile->nb < pile->next->nb && pile->nb < pile->next->next->nb)
	{
		if (pile->next->nb > pile->next->next->nb)
			actions = index ? "pa\nrb\npb" : "rra\nsa";
	}
	else
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "sb" : "sa";
		else
			actions = index ? "rrb" : "rra";
	}
	return (apply_one_three_sort(stacks, actions, index));
}

static int	one_two_sort(t_stacks *stacks, int index)
{
	int		len;
	t_pile	*pile;
	char	*action;

	pile = index ? stacks->b_pile : stacks->a_pile;
	len = ft_lstlen(pile);
	action = "";
	if (len == 2)
		if (pile->nb > pile->next->nb)
			action = index ? "rb" : "sa";
	return (apply_one_three_sort(stacks, action, index));
}

static int	put_min_top(t_stacks *stacks, int index)
{
	int		nbr;
	t_pile	*pile;
	char	*action;

	pile = index ? stacks->b_pile : stacks->a_pile;
	nbr = pile->nb;
	ft_lst_opposites(pile, &nbr, NULL);
	if (!(action = put_nbr_top(pile, index, ft_lstgetpos(pile, nbr), stacks)))
		return (1);
	if (append_actions(action, stacks))
		return (1);
	free(action);
	pile = index ? stacks->b_pile : stacks->a_pile;
	pile->p = 1;
	while ((stacks->rr)[1])
	{
		if (append_actions("ra", stacks))
			return (1);
		(stacks->rr)[1] -= 1;
	}
	return (0);
}

int			selection_sort(t_stacks *stacks, int index)
{
	int		i;
	char	*action;

	i = index ? ft_lstlen(stacks->b_pile) : ft_lstlen(stacks->a_pile);
	while (--i >= 3)
	{
		if (put_min_top(stacks, index))
			return (1);
		action = index ? "pa" : "pb";
		if (append_actions(action, stacks))
			return (1);
		if (index)
			(stacks->rr)[1] += 1;
	}
	if (i == 2)
		return (three_sort(stacks, index));
	else
		return (one_two_sort(stacks, index));
}
