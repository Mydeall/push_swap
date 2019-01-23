/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/23 18:05:00 by ccepre           ###   ########.fr       */
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

static int	choose_pivot_option(t_pile *pile, t_pile *pivot, int *option)
{
	int	nb_inf[2];
	int	nb_sup[2];
	int	k;
	int	nb_action;
	t_pile	*current;

	nb_inf[0] = 0;
	nb_inf[1] = 0;
	nb_sup[0] = 0;
	nb_sup[1] = 0;
	k = 0;
	current = pile;
	while (current)
	{
		nb_sup[0 + k] = current->nb > pivot->nb ? nb_sup[0 + k] + 1 : nb_sup[0 + k];
		nb_inf[0 + k] = current->nb < pivot->nb ? nb_inf[0 + k] + 1 : nb_inf[0 + k];
		if (current == pivot)
			k = 1;
		current = current->next;
	}
	*option = 0;
	if (nb_sup[0] > nb_sup[0] + 1)
		*option = 1;
	if (nb_inf[0] + 1 < nb_inf[1])
		k = 0;
	if (nb_sup[*option] + 1 + *option > nb_inf[k] + 3 - k)
		*option = 2 + k;
	nb_action = *option > 1 ? nb_inf[k] : nb_sup[*option];
	return (nb_action);
}

static char	*set_sort_action(t_pile *pile, t_pivot *p_options, int first,\
		int index)
{
	char	*actions;
	char	*action;
	char	*tmp;

	if (pile == pivot)
		action = p_options->option < 2 ? "ra" : "pb";
	else if (pile == first)
	{
		if (p_options->option == 0 || p_options->option == 3)
			action = index ? "ra" : "rb";
		else
			action = index ? "rra\n" : "rrb\n";
		if (!(actions = ft_strdup(action)))
			return (NULL);
		while (p_options->nb_actions--)
		{
			if (!p_options->nb_actions)
				action = index ? "rra" : "rrb";
			tmp = actions;
			if (!(actions = ft_strjoin(actions, action)))
				return (NULL);
			free(tmp);
		}
	}
	else if (((pile->nb < pivot->nb && index) || (pile->nb > pivot->nb &&\
					!index)) && pile->next)
		action = "rb";
	else
		action = "pa";
	if (pile != first)
	{
		if (!(action = ft_strdup(action)))
			return (1);
		if (!index)
			action[1] = action[1] == 'b' ? 'a' : 'b';
	}
	else
		action = actions;
	return (action);
}

static int	sort_sub_lst(t_stacks *stacks, char **operations,\
		t_pile *sorted, int index)
{
	t_pivot	*p_options;
	char	*action;
	t_pile	*pile;

	if (!(p_options = (t_pivot*)malloc(sizeof(t_pivot))))
		return (1);
	pile = index ? stacks->b_pile : stacks->a_pile;
	if (ft_lstlen(pile) < SUBLST_SIZE)
		return (little_list_sort(stacks, operations, index));
	if (!sorted)
		p_options->pivot = ft_lstgetlast(pile);
	else
	{
		p_options->pivot = pivot_choice(pile, sorted);
		p_options->nb_action = choose_pivot_option(pile, p_options->pivot,\
				&(p_options->option));
	}
	p_options->pivot->p = 1;
	while (pile != pivot)
	{
		if (!(action = set_sort_action(pile, p_options, first, index)))
			return (1);
		if (append_actions(action, stacks, operations))
			return (1);
		free(action);
		pile = index ? stacks->b_pile : stacks->a_pile;
	}
	action = index ? "pa" : "";
	if (*action && append_actions(action, stacks, operations))
		return (1);
	return (0);
}

static int	isolate_sub_lst(t_stacks *stacks, char **operations, int *first)
{
	printf("------ ISOLATE -------\n");
	while (stacks->a_pile->p && stacks->a_pile->nb != *first)
	{
		if (append_actions("ra", stacks, operations))
			return (1);
	}
	while (!(stacks->a_pile->p))
	{
		if (append_actions("pb", stacks, operations))
			return (1);
	}
	printf("----ISOLATE DONE-----\n");
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	getchar();
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, char **operations, t_pile **sorted)
{
	int	*first;
	int end;

	first = NULL;
	end = 0;
	printf("------ INIT ------\n");
	if (sort_sub_lst(stacks, operations, *sorted, 0))
		return (1);
	printf("------ INIT DONE ------\n");
	while (!end)
	{
		while (stacks->b_pile)
			if (sort_sub_lst(stacks, operations, *sorted, 1))
				return (1);
		if (!first)
		{
			if (!(first = (int*)malloc(sizeof(int))))
				return(1);
			*first = stacks->a_pile->nb; 
			if (append_actions("ra", stacks, operations))
				return (1);
		}
		if (isolate_sub_lst(stacks, operations, first))
			return (1);
		if (first && stacks->a_pile->nb == *first && !(stacks->b_pile))
			end = 1;
	}
	if (!*sorted)
		*sorted = stacks->a_pile;
	return (0);
}
