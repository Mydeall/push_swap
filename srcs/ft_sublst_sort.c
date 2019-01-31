/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_sublst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:51:35 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/30 18:07:32 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

t_pile	*pivot_choice(t_pile *pile, t_pile *sorted)
{
	int		min;
	int		max;
	t_pile	*current;
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
	i = ft_lstgetpos(pile, current->nb);
	current = pile;
	while (--i + 1)
		current = current->next;
	return (current);
}

char	*set_action(t_stacks *stacks, t_pile *pivot, t_pile *first, int index)
{
	char	*action;
	int		pos;
	char	*tmp;
	t_pile	*pile;

	pile = index ? stacks->b_pile : stacks->a_pile;
	if (pile == first)
	{
		pos = ft_lstgetpos(pile, pivot->nb);
		if (!(action = put_nbr_top(pile, index, pos, stacks)))
			return (NULL);
		tmp = action;
		if (!(action = index ? ft_strjoin(action, "pa") : ft_strdup(action)))
			return (NULL);
		free(tmp);
	}
	else if (((pile->nb <= pivot->nb && index) ||\
				(pile->nb >= pivot->nb && !index)) && pile->next)
	{
		if (!(action = index ? ft_strdup("rb") : ft_strdup("ra")))
			return (NULL);
	}
	else
		if (!(action = index ? ft_strdup("pa") : ft_strdup("pb")))
			return (NULL);
	return (action);
}

int		sort_sub_lst(t_stacks *stacks, char **operations,\
		t_pile *sorted, int index)
{
	t_pile	*pivot;
	char	*action;
	t_pile	*pile;
	t_pile 	*first;

//	printf("--------- SUB_LIST_SORT -----------\n");
	pile = index ? stacks->b_pile : stacks->a_pile;
	if (ft_lstlen(pile) < SUBLST_SIZE)
		return (little_list_sort(stacks, operations, index));
	first = NULL;
	pivot = pivot_choice(pile, sorted);
	pivot->p = 1;
	while (pile)
	{
	//	printf("boucle : %d\n", pivot->nb);
	//	ft_putlst(stacks->a_pile);
	//	ft_putlst(stacks->b_pile);
		if (!(action = set_action(stacks, pivot, first, index)))
			return (1);
		//printf("action : |%s|\n", action);
		if (append_actions(action, stacks, operations))
			return (1);
		free(action);
		if (pile == first)
			break ;
		if (!first && ((ft_strstr(action, "ra") && !index) ||\
				   	(ft_strstr(action, "rb") && index)))
			first = pile;
		pile = index ? stacks->b_pile : stacks->a_pile;
	//	ft_putlst(stacks->a_pile);
	//	ft_putlst(stacks->b_pile);
	//	printf("-------------\n");
	//	getchar();
	}
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("--------- SUB_LIST_SORT DONE -----------\n");
//	getchar();
	return (0);
}
