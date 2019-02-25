/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/25 10:46:33 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	save_pivot(t_stacks *stacks)
{
	t_pile	*current;

	while (stacks->a_pile->p)
	{
		if (stacks->a_pile->first)
		{
			current = stacks->a_pile;
			while (current && current->p)
				current = current->next;
			if (!current)
				break ;
		}
		if (append_actions("ra", stacks))
			return (1);
	}
	return (0);
}

static int	compute_nb_pivot(t_stacks *stacks)
{
	int		sub_size;
	t_pile	*current;

	sub_size = 0;
	current = stacks->a_pile;
	while (!current->p && ++sub_size)
		current = current->next;
	return (sub_size);
}

static int	isolate_sub_lst(t_stacks *stacks, t_pile *sorted)
{
	t_pile	*sublst;
	int		sub_size;
	t_pile	*pivot;

	if (save_pivot(stacks))
		return (1);
	if (!(sub_size = compute_nb_pivot(stacks)))
		return (0);
	if (!(sublst = ft_lstcpy(stacks->a_pile, sub_size - 1)))
		return (1);
	if (sub_size <= SUBLST_SIZE)
		return (sort_inf_subsize(stacks, sublst, sub_size));
	else
	{
		pivot = pivot_choice(sublst, sorted);
		pivot->p = 1;
		if (sort_sup_subsize(stacks, pivot))
			return (1);
		stacks->b_pile->p = 1;
		if (append_actions("pa", stacks))
			return (1);
	}
	ft_freelst(sublst);
	return (0);
}

static int	set_parameters(t_stacks *stacks, int *first,\
		int *end, t_pile **sorted)
{
	int		pos;
	t_pile	*current;

	*end = ft_lstlen(stacks->a_pile) > (SUBLST_SIZE - 1) ? 0 : 1;
	ft_lst_opposites(stacks->a_pile, first, NULL);
	if ((pos = ft_lstgetpos(stacks->a_pile, *first)) == -1)
		return (1);
	current = stacks->a_pile;
	while (pos-- > 0)
		current = current->next;
	current->first = 1;
	if (sort_sub_lst(stacks, *sorted, 0))
		return (1);
	if (stacks->a_pile->first && !(stacks->b_pile) && stacks->a_pile->p)
		*end = 1;
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, t_pile **sorted, char **operations)
{
	int		end;
	int		first;

	first = stacks->a_pile->nb;
	if (set_parameters(stacks, &first, &end, sorted))
		return (1);
	while (!end)
	{
		while (stacks->b_pile)
			if (sort_sub_lst(stacks, *sorted, 1))
				return (1);
		if (isolate_sub_lst(stacks, *sorted))
			return (1);
		if (stacks->a_pile->first && !(stacks->b_pile))
			break ;
	}
	if (!(*operations = ft_pooljoin(stacks->pool)))
		return (1);
	ft_freepool(stacks->pool);
	return (0);
}
