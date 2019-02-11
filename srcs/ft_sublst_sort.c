/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_sublst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:51:35 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:12:59 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	verif_remaining(t_stacks *stacks, t_pile *pivot,\
		t_pile *first, int index)
{
	t_pile	*pile;

	pile = index ? stacks->b_pile : stacks->a_pile;
	while (pile && pile != first)
	{
		if ((pile->nb > pivot->nb && index) ||\
				(pile->nb < pivot->nb && !index))
			return (1);
		pile = pile->next;
	}
	return (0);
}

static char	*set_action_first(t_stacks *stacks, t_pile *pivot, int index)
{
	int		pos;
	char	*tmp;
	t_pile	*pile;
	char	*action;

	pile = index ? stacks->b_pile : stacks->a_pile;
	pos = ft_lstgetpos(pile, pivot->nb);
	if (!(action = put_nbr_top(pile, index, pos, stacks)))
		return (NULL);
	tmp = action;
	if (!(action = index ? ft_strjoin(action, "pa") : ft_strdup(action)))
		return (NULL);
	free(tmp);
	return (action);
}

char		*set_action(t_stacks *stacks, t_pile *pivot, t_pile *first,\
		int index)
{
	char	*action;
	t_pile	*pile;

	pile = index ? stacks->b_pile : stacks->a_pile;
	if (pile == first)
		return (set_action_first(stacks, pivot, index));
	else if (((pile->nb <= pivot->nb && index) ||\
				(pile->nb >= pivot->nb && !index)) && pile->next)
	{
		if (index && !verif_remaining(stacks, pivot, first, index))
			action = ft_strdup("except");
		else if (!(action = index ? ft_strdup("rb") : ft_strdup("ra")))
			return (NULL);
	}
	else if (!(action = index ? ft_strdup("pa") : ft_strdup("pb")))
		return (NULL);
	return (action);
}

static int	sort_lst(t_stacks *stacks, t_pile *pivot,\
		t_pile *first, int index)
{
	char	*action;
	t_pile	*pile;

	pile = index ? stacks->b_pile : stacks->a_pile;
	while (pile)
	{
		pile = index ? stacks->b_pile : stacks->a_pile;
		if (!(action = set_action(stacks, pivot, first, index)))
			return (1);
		if (ft_strcmp(action, "except"))
			if (append_actions(action, stacks))
				return (1);
		if (!ft_strcmp(action, "except") || pile == first)
		{
			free(action);
			if (pile == first)
				break ;
			first = pile;
			continue ;
		}
		if (!first && ((ft_strstr(action, "ra") && !index) ||\
					(ft_strstr(action, "rb") && index)))
			first = pile;
		free(action);
	}
	return (0);
}

int			sort_sub_lst(t_stacks *stacks, t_pile *sorted, int index)
{
	t_pile	*pivot;
	t_pile	*pile;
	t_pile	*first;

	pile = index ? stacks->b_pile : stacks->a_pile;
	if (ft_lstlen(pile) < SUBLST_SIZE)
		return (selection_sort(stacks, index));
	first = NULL;
	pivot = pivot_choice(pile, sorted);
	pivot->p = 1;
	if (sort_lst(stacks, pivot, first, index))
		return (1);
	return (0);
}
