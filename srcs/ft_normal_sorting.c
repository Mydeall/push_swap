/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_normal_sorting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:24:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/06 15:00:09 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static t_pile	*ft_getnode(t_pile *lst, int pos)
{
	t_pile	*current;
	int		i;

	current = lst;
	i = -1;
	while (++i < pos)
		current = current->next;
	return (current);
}

static int		select_lst(t_pile *lst, int *start, int *end)
{
	t_pile	*current;

	current = lst;
	*start = 0;
	while (current && current->p && ++(*start))
		current = current->next;
	if (!current)
		return (1);
	*end = *start - 1;
	while (current && !current->p)
	{
		current = current->next;
		(*end)++;
	}
	return (0);
}

static t_pile	*insert_node_behind(t_pile **prev, t_pile **current,\
		t_pile *target, t_pile *lst)
{
	t_pile	*tmp;

	if ((*prev))
		(*prev)->next = (*current)->next;
	else
		tmp = (*current)->next;
	(*current)->next = target->next;
	target->next = *current;
	*current = *prev ? (*prev)->next : tmp;
	if (target->next == lst)
		lst = *current;
	return (lst);
}

static t_pile	*separate_lst(t_pile *lst, int start, int end)
{
	t_pile	*current;
	t_pile	*pivot;
	t_pile	*prev;

	pivot = ft_getnode(lst, end);
	pivot->p = 1;
	current = ft_getnode(lst, start);
	prev = start ? ft_getnode(lst, start - 1) : NULL;
	while (current && current != pivot)
	{
		if (current->nb > pivot->nb)
			lst = insert_node_behind(&prev, &current, pivot, lst);
		else
		{
			prev = current;
			current = current->next;
		}
	}
	return (lst);
}

t_pile			*ft_sort(t_pile *lst)
{
	int finished;
	int	start;
	int	end;

	if (!lst)
		return (lst);
	finished = 0;
	start = 0;
	end = ft_lstlen(lst) - 1;
	while (!finished)
	{
		lst = separate_lst(lst, start, end);
		if (select_lst(lst, &start, &end))
			finished = 1;
	}
	return (lst);
}
