/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isolate_sublst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 16:54:12 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/08 16:59:04 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	split_sublst(t_stacks *stacks, t_pile *pivot)
{
	char	*action;

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
	return (0);
}

int			sort_sup_subsize(t_stacks *stacks, t_pile *pivot)
{
	char	*action;
	int		pos;

	if (split_sublst(stacks, pivot))
		return (1);
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

static int	recover_smallest(t_stacks *stacks, int pos, int *len)
{
	char	*action;

	if (!(action = put_nbr_top(stacks->b_pile, 1, pos, stacks)))
		return (1);
	if (append_actions(action, stacks))
		return (1);
	free(action);
	stacks->b_pile->p = 1;
	if (append_actions("pa", stacks))
		return (1);
	(*len)++;
	return (0);
}

int			sort_inf_subsize(t_stacks *stacks, t_pile *sublst, int sub_size)
{
	int		len;
	int		pos;

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
				if (recover_smallest(stacks, pos, &len))
					return (1);
		}
		else if (append_actions("pb", stacks))
			return (1);
	}
	ft_freelst(sublst);
	return (0);
}
