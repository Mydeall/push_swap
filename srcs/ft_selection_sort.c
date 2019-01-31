/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sublist_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:48:45 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/31 17:18:14 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	apply_one_three_sort(t_stacks *stacks, char **operations,\
		char *actions, int index)
{
	t_pile	*current;

	if (*actions && append_actions(actions, stacks, operations))
		return (1);
	current = stacks->a_pile;
	while (!index && current)
	{
		current->p = 1;
		current = current->next;
	}
	while ((stacks->rr)[1])
	{
		if (append_actions("ra", stacks, operations))
			return (1);
		(stacks->rr)[1]--;
	}
	while (stacks->b_pile)
	{
		stacks->b_pile->p = 1;
		if (append_actions("pa\nra", stacks, operations))
			return (1);
	}
	return (0);
}

static int	three_sort(t_stacks *stacks, char **operations, int index)
{
	char	*actions;
	t_pile	*pile;

//	printf("--------THREE SORT-------\n");
	pile = index ? stacks->b_pile : stacks->a_pile;
	actions = "";
	if (pile->nb > pile->next->nb && pile->nb > pile->next->next->nb)
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "rb" : "ra";
		else
			actions = index ? "rb\nsb" : "ra\nsa";
	}
	else if (pile->nb < pile->next->nb && pile->nb < pile->next->next->nb)
	{
		if (pile->next->nb > pile->next->next->nb)
			actions = index ? "pa\nrb\npb" : "rra\nsa";
	}
	else
	{
		if (pile->next->nb < pile->next->next->nb)
			actions = index ? "sb" : "sa";
		else
			actions = index ? "rrb" : "rra";
	}
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("----THREE SORT DONE-----\n");
//	getchar();
	return (apply_one_three_sort(stacks, operations, actions, index));
}

static int	one_two_sort(t_stacks *stacks, char **operations, int index)
{
	int		len;
	t_pile	*pile;
	char	*action;

	pile = index ? stacks->b_pile : stacks->a_pile;
	len = ft_lstlen(pile);
//	printf("----ONE TWO SORT-----\n");
	action = "";
	if (len == 2)
		if (pile->nb > pile->next->nb)
			action = index ? "rb" : "sa";
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("----ONE TWO SORT DONE-----\n");
//	getchar();
	return (apply_one_three_sort(stacks, operations, action, index));
}

char	*put_nbr_top(t_pile *pile, int index, int pos, t_stacks *stacks)
{
	char	*action;
	int		len;
	int		side;
	char	*tmp;
	char	*result;

	len = ft_lstlen(pile);
	side = pos - (stacks->rr)[index] <= len - pos - (stacks->rrr)[index] ? -1 : 1;
	action = side == -1 ? "rr\n" : "rrr\n";
	if (!(result = ft_strnew(1)))
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
		tmp = result;
		if (!(result = ft_strjoin(result, action)))
			return (NULL);;
		free(tmp);
		pos += side;
	}
	return (result);
}

int	little_list_sort(t_stacks *stacks, char **operations, int index)
{
	int		nbr;
	t_pile	*pile;
	int		i;
	int		pos;
	char	*action;

//	printf("-----LITTLE LIST------\n");
	pile = index ? stacks->b_pile : stacks->a_pile;
	i = ft_lstlen(pile);
	while (--i >= 3)
	{
//		printf("-----SELECTION SORT------\n");
		pile = index ? stacks->b_pile : stacks->a_pile;
		nbr = pile->nb;
		ft_lst_opposites(pile, &nbr, NULL);
		pos = ft_lstgetpos(pile, nbr);
		if (!(action = put_nbr_top(pile, index, pos, stacks)))
			return (1);
//		printf("actions selction push top : |%s|", action);
		if (append_actions(action, stacks, operations))
			return (1);
		free(action);
		pile = index ? stacks->b_pile : stacks->a_pile;
		pile->p = 1;
		while ((stacks->rr)[1])
		{
			if (append_actions("ra", stacks, operations))
				return (1);
			(stacks->rr)[1] -= 1;
		}
		action = index ? "pa" : "pb";
		if (append_actions(action, stacks, operations))
			return (1);
		(stacks->rr)[1] += 1;
//		ft_putlst(stacks->a_pile);
//		ft_putlst(stacks->b_pile);
//		printf("----SELECTION SORT DONE-----\n");
//		getchar();
	}
	if (i == 2)
		return (three_sort(stacks, operations, index));
	else
		return (one_two_sort(stacks, operations, index));
}
