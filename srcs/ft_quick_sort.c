/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/17 18:46:41 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	three_sort(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	char	*actions;

//	printf("--------THREE SORT-------\n");
	actions = "";
	if (stacks->a_pile->nb < stacks->a_pile->next->nb &&\
		   	stacks->a_pile->nb < stacks->a_pile->next->next->nb)
	{
		if (stacks->a_pile->next->nb > stacks->a_pile->next->next->nb)
			actions = "pb\nsa\npa";
	}
	else if (stacks->a_pile->nb < stacks->a_pile->next->nb ||\
		   	stacks->a_pile->nb < stacks->a_pile->next->next->nb)
	{
		if (stacks->a_pile->next->nb > stacks->a_pile->next->next->nb)
			actions = "rra";
		else
			actions = "sa";
	}
	else
	{
		if (stacks->a_pile->next->nb > stacks->a_pile->next->next->nb)
			actions = "ra\nsa";
		else
			actions = "ra";
	}
	if (append_actions(actions, stacks, operations, fcts_tab))
		return (1);
	while (stacks->a_pile)
	{
		stacks->a_pile->p = 1;
		if (append_actions("pb", stacks, operations, fcts_tab))
			return (1);
	}
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	getchar();
//	printf("----THREE SORT DONE-----\n");
	return (0);
}

static int	little_list_sort(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	int len;
	int pos;
	int	min;
	t_pile	*current;
	int	i;

	len = ft_lstlen(stacks->a_pile);
	i = len;
	while (--i >= 3)
	{
//		printf("-----SELECTION SORT------\n");
		current = stacks->a_pile;
		min = current->nb;
		while (current)
		{
			if (current->nb < min)
				min = current->nb;
			current = current->next;
		}
//		ft_putlst(stacks->a_pile);
		pos = ft_lstgetpos(stacks->a_pile, min);
//		printf("min : %d\npos : %d\n", min, pos);
		if (pos <= len / 2)
		{
			while (pos--)
				if (append_actions("ra", stacks, operations, fcts_tab))
					return (1);
		}
		else
			while (++pos <= len)
				if (append_actions("rra", stacks, operations, fcts_tab))
					return (1);
		stacks->a_pile->p = 1;
		if (append_actions("pb", stacks, operations, fcts_tab))
			return (1);
//		ft_putlst(stacks->a_pile);
//		ft_putlst(stacks->b_pile);
//		getchar();
//		printf("----SELECTION SORT DONE-----\n");
	}
	if (i == 2)
		return (three_sort(stacks, operations, fcts_tab));
	else
	{
//		printf("----ONE TWO SORT-----\n");
		if (len == 2)
			if (stacks->a_pile->nb > stacks->a_pile->next->nb)
				if (append_actions("sa", stacks, operations, fcts_tab))
					return (1);
		while (stacks->a_pile)
		{
			stacks->a_pile->p = 1;
			if (append_actions("pb", stacks, operations, fcts_tab))
				return (1);
		}
//		ft_putlst(stacks->a_pile);
//		ft_putlst(stacks->b_pile);
//		getchar();
//		printf("----ONE TWO SORT DONE-----\n");
	}
	return (0);
}

static int	sort_sub_lst(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab)
{
	t_pile	*pivot;
	char	*action;

//	printf("--------SORT-------\n");
	if (ft_lstlen(stacks->a_pile) < SUBLST_SIZE)
		return (little_list_sort(stacks, operations, fcts_tab));
	pivot = ft_lstgetlast(stacks->a_pile);
	pivot->p = 1;
	while (stacks->a_pile != pivot)
	{
		if (stacks->a_pile->nb > pivot->nb && stacks->a_pile->next)
			action = "ra";
		else
			action = "pb";
		if (append_actions(action, stacks, operations, fcts_tab))
			return (1);
	}
	if (append_actions("pb", stacks, operations, fcts_tab))
		return (1);
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	getchar();
//	printf("----SORT DONE-----\n");
	return (0);
}

static int	isolate_sub_lst(t_stacks *stacks, char **operations, t_oper_fcts *fcts_tab, int *last)
{
//	printf("------ ISOLATE -------\n");
	while (stacks->b_pile->p && stacks->b_pile->nb != *last)
	{
		if (append_actions("rb", stacks, operations, fcts_tab))
			return (1);
	}
	while (!(stacks->b_pile->p))
	{
		if (append_actions("pa", stacks, operations, fcts_tab))
			return (1);
	}
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("----ISOLATE DONE-----\n");
//	getchar();
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, char **operations,  t_oper_fcts *fcts_tab)
{
	int		*last;
	int	len;
	int end;

	last = NULL;
	len = ft_lstlen(stacks->a_pile);
	end = 0;
	if (len < SUBLST_SIZE)
	{
		if (little_list_sort(stacks, operations, fcts_tab))
			return (1);
		end = 1;
	}
	while (!end)
	{
		while (stacks->a_pile)
			if (sort_sub_lst(stacks, operations, fcts_tab) == 1)
				return (1);
		if (!last)
		{
			if (!(last = (int*)malloc(sizeof(int))))
				return(1);
			*last = stacks->b_pile->nb; 
			if (append_actions("rb", stacks, operations, fcts_tab))
				return (1);
		}
		if (isolate_sub_lst(stacks, operations, fcts_tab, last) == 1)
			return (1);
		if (last && stacks->b_pile->nb == *last && !(stacks->a_pile))
			end = 1;
	}
	while (stacks->b_pile)
		if (append_actions("pa", stacks, operations, fcts_tab))
			return (1);
//	ft_putlst(*a_pile);
//	ft_putlst(*b_pile);
//	printf("OK\n");
	return (0);
}
