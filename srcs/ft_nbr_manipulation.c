/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:29:36 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:07:22 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			ft_lst_opposites(t_pile *pile, int *min, int *max)
{
	t_pile *current;

	if (!(pile))
		return (1);
	current = pile;
	while (current)
	{
		if (max && current->nb > *max)
			*max = current->nb;
		else if (min && current->nb < *min)
			*min = current->nb;
		current = current->next;
	}
	return (0);
}

char		*put_nbr_top(t_pile *pile, int index, int pos, t_stacks *stacks)
{
	char	*action;
	int		len;
	int		side;
	char	*result;

	len = ft_lstlen(pile);
	side = pos - (stacks->rr)[index] <= len - pos - (stacks->rrr)[index] ?
		-1 : 1;
	action = side == -1 ? "rr\n" : "rrr\n";
	if (!(result = side == 1 ? ft_strnew((len - pos) * 4) : ft_strnew(pos * 3)))
		return (NULL);
	while ((pos && side == -1) || (pos < len && side == 1))
	{
		if (side == -1 && (stacks->rr)[index] == 0)
			action = index ? "rb\n" : "ra\n";
		else if (side == 1 && (stacks->rrr)[index] == 0)
			action = index ? "rrb\n" : "rra\n";
		(stacks->rr)[index] = !ft_strcmp(action, "rr\n") ?\
							(stacks->rr)[index] - 1 : (stacks->rr)[index];
		(stacks->rrr)[index] = !ft_strcmp(action, "rrr\n") ?\
							(stacks->rrr[index]) - 1 : (stacks->rrr)[index];
		ft_strcat(result, action);
		pos += side;
	}
	return (result);
}

t_pile		*pivot_choice(t_pile *pile, t_pile *sorted)
{
	t_pile	*current;
	int		min;
	int		max;
	int		len;
	int		i;

	min = pile->nb;
	max = pile->nb;
	ft_lst_opposites(pile, &min, &max);
	len = ft_lstlen(pile);
	current = sorted;
	i = 0;
	while (i < len / 2)
	{
		if (current->nb >= min && current->nb <= max)
			i++;
		current = current->next;
	}
	if ((i = ft_lstgetpos(pile, current->nb)) == -1)
		return (NULL);
	current = pile;
	while (--i + 1)
		current = current->next;
	return (current);
}
