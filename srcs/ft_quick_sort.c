/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/06 17:52:01 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

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

static int	sort_sup_subsize(t_stacks *stacks, t_pile *pivot)
{
	char	*action;
	int		pos;

	while (!(stacks->a_pile->p))
	{
		if (stacks->a_pile->nb == pivot->nb)
			action = ft_strdup("pb");
		else if (!(action = set_action(stacks, pivot, NULL, 0)))
			return (1);
		if (ft_strstr(action, "ra"))
			(stacks->rrr)[1] += 1;
		if (append_actions(action, stacks))
			return (1);
		free(action);
	}
	pos = ft_lstgetpos(stacks->b_pile, pivot->nb);
	if (!(action = put_nbr_top(stacks->b_pile, 1, pos, stacks)))
		return (1);
	while ((stacks->rrr)[1])
	{
		if (append_actions("rra", stacks))
			return (1);
		(stacks->rrr)[1] -= 1;
	}
	if (append_actions(action, stacks))
		return (1);
	free(action);
	return (0);
}

static int	sort_inf_subsize(t_stacks *stacks, t_pile *sublst, int sub_size)
{
	int		len;
	int		pos;
	char	*action;

	len = sub_size;
	sublst = ft_sort(sublst);
	while (len--)
	{
		if (stacks->a_pile->nb == sublst->nb)
		{
			stacks->a_pile->p = 1;
			if (append_actions("ra", stacks))
				return (1);
			ft_delnode(&sublst, sublst->nb);
			if (!sublst)
				break ;
			pos = ft_lstgetpos(stacks->b_pile, sublst->nb);
			if (pos != -1 && len)
			{
				action = put_nbr_top(stacks->b_pile, 1, pos, stacks);
				if (append_actions(action, stacks))
					return (1);
				free(action);
				stacks->b_pile->p = 1;
				if (append_actions("pa", stacks))
					return (1);
				len++;
			}
		}
		else if (append_actions("pb", stacks))
			return (1);
	}
	ft_freelst(sublst);
	return (0);
}

static int	isolate_sub_lst(t_stacks *stacks, t_pile *sorted)
{
	t_pile	*sublst;
	int		sub_size;
	t_pile	*pivot;

	if (save_pivot(stacks))
		return (1);
	sub_size = 0;
	sublst = stacks->a_pile;
	while (!sublst->p && ++sub_size)
		sublst = sublst->next;
	if (!sub_size)
		return (0);
	if (!(sublst = ft_lstcpy(stacks->a_pile, 0, sub_size - 1)))
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

int			ft_quick_sort(t_stacks *stacks, t_pile **sorted, char **operations)
{
	int		end;
	int		first;
	int		pos;
	t_pile	*current;

	end = ft_lstlen(stacks->a_pile) > SUBLST_SIZE ? 0 : 1;
	ft_lst_opposites(stacks->a_pile, &first, NULL);
	pos = ft_lstgetpos(stacks->a_pile, first);
	current = stacks->a_pile;
	while (pos-- > 0)
		current = current->next;
	current->first = 1;
	if (sort_sub_lst(stacks, *sorted, 0))
		return (1);
	if (stacks->a_pile->first && !(stacks->b_pile) && stacks->a_pile->p)
		end = 1;
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
