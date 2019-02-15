/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:55:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/15 12:58:31 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		swap(char *action, t_pile **a_pile, t_pile **b_pile)
{
	t_pile	*tmp;

	if ((action[1] != 'b' && (!(*a_pile) || !(*a_pile)->next)) ||\
			(action[1] != 'a' && (!(*b_pile) || !(*b_pile)->next)))
		return ;
	if (action[1] != 'b')
	{
		tmp = (*a_pile)->next;
		if ((*a_pile)->next)
			(*a_pile)->next = (*a_pile)->next->next;
		ft_lstadd(a_pile, tmp);
	}
	if (action[1] != 'a')
	{
		tmp = (*b_pile)->next;
		if ((*b_pile)->next)
			(*b_pile)->next = (*b_pile)->next->next;
		ft_lstadd(b_pile, tmp);
	}
}

void		push(char *action, t_pile **a_pile, t_pile **b_pile)
{
	t_pile	*tmp;

	if ((action[1] == 'b' && !(*a_pile)) ||\
			(action[1] == 'a' && !(*b_pile)))
		return ;
	if (action[1] == 'a' && *b_pile)
	{
		tmp = *b_pile;
		*b_pile = (*b_pile)->next;
		ft_lstadd(a_pile, tmp);
	}
	else if (action[1] == 'b' && *a_pile)
	{
		tmp = *a_pile;
		*a_pile = (*a_pile)->next;
		ft_lstadd(b_pile, tmp);
	}
}

static void	rotation(t_pile **pile, int side)
{
	t_pile	*current;
	t_pile	*tmp;

	if (side > 0)
	{
		tmp = *pile;
		*pile = (*pile)->next;
		ft_lstaddend(pile, tmp);
	}
	else
	{
		current = *pile;
		while (current->next->next)
			current = current->next;
		ft_lstadd(pile, current->next);
		current->next = NULL;
	}
}

void		rotate(char *action, t_pile **a_pile, t_pile **b_pile)
{
	int side;
	int	len;

	len = ft_strlen(action);
	if ((action[len - 1] != 'b' && (!(*a_pile) || !(*a_pile)->next)) ||\
			(action[len - 1] != 'a' && (!(*b_pile) || !(*b_pile)->next)))
		return ;
	side = len == 2 ? 1 : -1;
	action = len == 2 ? action + 1 : action + 2;
	if (*action != 'b' && ft_lstlen(*a_pile) > 1)
		rotation(a_pile, side);
	if (*action != 'a' && ft_lstlen(*b_pile) > 1)
		rotation(b_pile, side);
}

t_oper_fcts	*make_struct(void)
{
	t_oper_fcts *fcts_tab;

	if (!(fcts_tab = (t_oper_fcts*)malloc(sizeof(t_oper_fcts) * 3)))
		return (NULL);
	fcts_tab[0].action = 's';
	fcts_tab[0].f = &swap;
	fcts_tab[1].action = 'p';
	fcts_tab[1].f = &push;
	fcts_tab[2].action = 'r';
	fcts_tab[2].f = &rotate;
	return (fcts_tab);
}
