/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 17:21:04 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/*
static int	three_sort(t_stack *stacks)
{
	if ((*a_pile)->nb < ((*a_pile)->next)->nb &&\
		   	(*a_pile)->nb < (*a_pile)->next->next->nb)
	{
		if (((*a_pile)->next)->nb > ((*a_pile)->next->next)->nb)
		{
			push("pb", a_pile, b_pile);
			swap("sa", a_pile, b_pile);
			push("pa", a_pile, b_pile);
			if (add_operation(operations, "pb\nsa\npa", 0))
				return (1);
		}
	}
	else if ((*a_pile)->nb < ((*a_pile)->next)->nb ||\
		   	(*a_pile)->nb < (*a_pile)->next->next->nb)
	{
		if (((*a_pile)->next)->nb > ((*a_pile)->next->next)->nb)
		{
			rotate("rra", a_pile, b_pile);	
			if (add_operation(operations, "rra", 0))
				return (1);
		}
		else
		{
			rotate("sa", a_pile, b_pile);	
			if (add_operation(operations, "sa", 0))
				return (1);
		}
	}
	else
	{
		if (((*a_pile)->next)->nb > ((*a_pile)->next->next)->nb)
		{
			rotate("ra", a_pile, b_pile);	
			swap("sa", a_pile, b_pile);	
			if (add_operation(operations, "ra\nsa", 0))
				return (1);
		}
		else
		{
			rotate("ra", a_pile, b_pile);	
			if (add_operation(operations, "ra", 0))
				return (1);
		}
	}
	return (1);
}
*/

static int	add_operation(char **operations, char *action, int end)
{
	char	*tmp;
	char	*end_str;

	tmp = *operations;
	end_str = "";
	if (!end)
		end_str = "\n";
	if (!(*operations = ft_strjoinarg(3, *operations, action, end_str)))
		return (1);
	free(tmp);
	return (0);
}

static int	sort_sub_lst(t_stack *stacks)
{
	t_pile	*pivot;
	char	*action;

//	printf("--------SORT-------\n");
	pivot = ft_lstgetlast((*stacks).a_pile);
//	printf("pivot : %d\n", pivot->nb);
	pivot->p = 1;
	while ((*stacks).a_pile != pivot)
	{
		if ((*a_pile)->nb > pivot->nb && (*a_pile)->next)
		{
			action = "ra";
			rotate(action, &((*stacks).a_pile), &((*stacks).b_pile));
		}
		else
		{
			action = "pb";
			push(action, &((*stacks).a_pile), &((*stacks).b_pile));
		}
		if (add_operation(&((*stacks).operations), action, 0))
			return (1);
	}
	push("pb", &((*stacks).a_pile), &((*stacks).b_pile));
	if (add_operation(operations, "pb", 0))
		return (1);
//	ft_putlst(*a_pile);
//	ft_putlst(*b_pile);
//	getchar();
//	printf("----SORT DONE-----\n");
	return (0);
}

static int	isolate_sub_lst(t_stacks *stacks, int *last)
{
//	printf("------ ISOLATE -------\n");
	while ((*stacks).b_pile->p && (*stacks).b_pile->nb != *last)
	{
		if (add_operation((*stacks).operations, "rb", 0))
			return (1);
		rotate("rb", &((*stacks).a_pile), &((*stacks).b_pile));
	}
	while (!((*stacks).b_pile)->p)
	{
		if (add_operation(operations, "pa", 0))
			return (1);
		push("pa", &((*stacks).a_pile), &((*stacks).b_pile));
	}
//	ft_putlst(*a_pile);
//	ft_putlst(*b_pile);
//	printf("----ISOLATE DONE-----\n");
//	getchar();
	return (0);
}

char		*ft_quick_sort(t_stacks *stacks)
{
	int		*last;
	int		end;

	end = 0;
	last = NULL;
	while (!end)
	{
		while ((*stacks).a_pile)
		{
			if (sort_sub_lst(stacks) == 1)
				return (1);
		}
		if (!last)
		{
			if (!(last = (int*)malloc(sizeof(int))))
				return(1);
			*last = (*stacks).b_pile->nb; 
			if (add_operation(&operations, "rb", 0))
				return (1);
			rotate("rb", (*stacks).a_pile, (*stacks).b_pile);
		}
		if (isolate_sub_lst(stacks, last) == 1)
			return (1);
		if (last && (*b_pile)->nb == *last && !(*a_pile))
			end = 1;
	}
	end = 0;
	while ((*stacks).b_pile)
	{
		if (!(*stacks).b_pile->next)
			end = 1;
		if (add_operation(&((*stacks).operations), "pa", end))
			return (1);
		push("pa", (*stacks).a_pile, (*stacks).b_pile);
	}
//	ft_putlst(*a_pile);
//	ft_putlst(*b_pile);
//	printf("OK\n");
	return (0);
}
