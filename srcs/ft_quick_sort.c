/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/22 15:57:10 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static t_pile	*pivot_choice(t_pile *pile, t_pile *sorted)
{
	int		min;
	int		max;
	t_pile	*current;
	int		len;
	int		i;

	printf("----- PIVOT CHOICE ------\n");
	ft_lst_opposites(pile, &min, &max);
	len = ft_lstlen(pile);
	current = sorted;
	ft_putlst(pile);
	ft_putlst(sorted);
	i = 0;
	while (i < len / 2)
	{
		if (current->nb >= min && current->nb <= max)
			i++;
		current = current->next;
	}
	i = ft_lstgetpos(pile, current->nb);
	current = pile;
	while (--i + 1)
		current = current->next;
	printf("PIVOT : %d\n", current->nb);
	printf("----- PIVOT CHOICE END------\n");
	return (current);
}

static int	initialization(t_stacks *stacks, char **operations,\
		t_oper_fcts *fcts_tab, t_pile *sorted)
{
	t_pile	*pivot;
	char	*action;

	printf("-------INIT-------\n");
	if (!sorted)
		pivot = ft_lstgetlast(stacks->a_pile);
	else
		pivot = pivot_choice(stacks->a_pile, sorted);
	pivot->p = 1;
	while (stacks->a_pile != pivot)
	{
		printf("a_pile : %p : %d\n", stacks->a_pile, stacks->a_pile->nb);
		printf("pivot : %p : %d\n", pivot, pivot->nb);
		getchar();
		if (stacks->a_pile->nb > pivot->nb && stacks->a_pile->next)
			action = "ra";
		else
			action = "pb";
		if (append_actions(action, stacks, operations, fcts_tab))
			return (1);
	}
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----INIT DONE-----\n");
	return (0);
}

static int	sort_sub_lst(t_stacks *stacks, char **operations,\
		t_oper_fcts *fcts_tab, t_pile *sorted)
{
	t_pile	*pivot;
	char	*action;

	printf("--------SORT-------\n");
	if (ft_lstlen(stacks->b_pile) < SUBLST_SIZE)
		return (little_list_sort(stacks, operations, fcts_tab));
	if (!sorted)
		pivot = ft_lstgetlast(stacks->b_pile);
	else
		pivot = pivot_choice(stacks->b_pile, sorted);
	pivot->p = 1;
	while (stacks->b_pile != pivot)
	{
		if (stacks->b_pile->nb < pivot->nb && stacks->b_pile->next)
			action = "rb";
		else
			action = "pa";
		if (append_actions(action, stacks, operations, fcts_tab))
			return (1);
	}
	if (append_actions("pa", stacks, operations, fcts_tab))
		return (1);
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	printf("----SORT DONE-----\n");
	return (0);
}
static int	isolate_sub_lst(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab, int *first)
{
	printf("------ ISOLATE -------\n");
	while (stacks->a_pile->p && stacks->a_pile->nb != *first)
	{
		if (append_actions("ra", stacks, operations, fcts_tab))
			return (1);
	}
	while (!(stacks->a_pile->p))
	{
		if (append_actions("pb", stacks, operations, fcts_tab))
			return (1);
	}
	printf("----ISOLATE DONE-----\n");
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, char **operations,\
		t_oper_fcts *fcts_tab, t_pile **sorted)
{
	int	*first;
	int	len;
	int end;

	first = NULL;
	len = ft_lstlen(stacks->a_pile);
	end = 0;
	if (len < SUBLST_SIZE)
	{
		while (stacks->a_pile)
			if (append_actions("pb", stacks, operations, fcts_tab))
				return (1);
		if (little_list_sort(stacks, operations, fcts_tab))
			return (1);
		end = 1;
	}
	if (!(sorted) || (!end && initialization(stacks, operations, fcts_tab, *sorted)))
		return (1);
	printf("HERE\n");
	while (!end)
	{
		while (stacks->b_pile)
			if (sort_sub_lst(stacks, operations, fcts_tab, *sorted))
				return (1);
		if (!first)
		{
			if (!(first = (int*)malloc(sizeof(int))))
				return(1);
			*first = stacks->a_pile->nb; 
			if (append_actions("ra", stacks, operations, fcts_tab))
				return (1);
		}
		if (isolate_sub_lst(stacks, operations, fcts_tab, first))
			return (1);
		if (first && stacks->a_pile->nb == *first && !(stacks->b_pile))
			end = 1;
	}
	if (!*sorted)
	{
		*sorted = stacks->a_pile;
		printf("sorrted by random mean\n");
	}
	return (0);
}
