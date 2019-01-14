/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:55:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/11 16:43:14 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

void		swap(char *operation, t_pile **a_pile, t_pile **b_pile)
{
	if (operation[1] != 'b')
		ft_swap(&((*a_pile)->nb), &((*a_pile)->next)->nb);
	if (operation[1] != 'a')
		ft_swap(&((*b_pile)->nb), &((*b_pile)->next)->nb);
}

void		push(char *operation, t_pile **a_pile, t_pile **b_pile)
{
	t_pile	*tmp;

	if (operation[1] == 'a' && *b_pile)
	{
		tmp = *b_pile;
		*b_pile = (*b_pile)->next;
		ft_lstadd(a_pile, tmp);
	}
	else if (operation[1] == 'b' && *a_pile)
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

void		rotate(char *operation, t_pile **a_pile, t_pile **b_pile)
{
	int side;

	side = ft_strlen(operation) == 2 ? 1 : -1;
	operation = ft_strlen(operation) == 2 ? operation + 1 : operation + 2;
	if (*operation != 'b' && ft_lstlen(*a_pile) > 1)
		rotation(a_pile, side);
	if (*operation != 'a' && ft_lstlen(*b_pile) > 1)
		rotation(b_pile, side);
}

t_oper_fcts	*make_struct(void)
{
	t_oper_fcts *fcts_tab;

	if (!(fcts_tab = (t_oper_fcts*)malloc(sizeof(t_oper_fcts) * 3)))
		return (NULL);
	fcts_tab[0].operation = 's';
	fcts_tab[0].f = &swap;
	fcts_tab[1].operation = 'p';
	fcts_tab[1].f = &push;
	fcts_tab[2].operation = 'r';
	fcts_tab[2].f = &rotate;
	return (fcts_tab);
}
