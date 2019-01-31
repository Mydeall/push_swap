/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:55:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/31 14:56:14 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

void		swap(char *action, t_pile **a_pile, t_pile **b_pile)
{
	if (action[1] != 'b')
		ft_swap(&((*a_pile)->nb), &((*a_pile)->next)->nb);
	if (action[1] != 'a')
		ft_swap(&((*b_pile)->nb), &((*b_pile)->next)->nb);
}

void		push(char *action, t_pile **a_pile, t_pile **b_pile)
{
	t_pile	*tmp;

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
		tmp = current->next;
		ft_lstadd(pile, tmp);
		current->next = NULL;
	}
}

void		rotate(char *action, t_pile **a_pile, t_pile **b_pile)
{
	int side;

	side = ft_strlen(action) == 2 ? 1 : -1;
	action = ft_strlen(action) == 2 ? action + 1 : action + 2;
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
