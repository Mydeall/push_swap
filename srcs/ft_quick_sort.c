/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:52:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/24 19:17:37 by ccepre           ###   ########.fr       */
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

static int	choose_pivot_option(t_pile *pile, t_pile *pivot, int *option, int index)
{
	int	nb_up;
	int	nb_down;
	int	k;
	int	nb_action;
	t_pile	*current;

	nb_down = 0;
	nb_up = 0;
	k = 0;
	current = pile;
	while (current)
	{
		if (k && ((!index && current->nb > pivot->nb) || (index && current->nb < pivot->nb)))
			nb_down++;
		else if (!k && ((!index && current->nb > pivot->nb) || (index && current->nb < pivot->nb)))
			nb_up++;
		if (current == pivot)
			k = 1;
		current = current->next;
	}
	*option = 0;
	if (nb_up > nb_down + 1)
		*option = 1;
	nb_action = *option == 0 ? nb_up : nb_down;
	return (nb_action + 1);
}

static char	*set_sort_action(t_pile *pile, t_pivot *p_options, t_pile *first,\
		int index)
{
	char	*actions;
	char	*action;
	char	*tmp;

//	printf("p_option : option = %d | nb_action = %d | index = %d\n", p_options->option, p_options->nb_action, index);
//	printf("pile nb : %d\n", pile->nb);
//	if (first)
//	printf("first : %d\n", first->nb);
	if (pile == p_options->pivot && pile != first)
		action = p_options->option < 2 ? "rb" : "pa";
	else if (pile == first)
	{
		action = index ? "rb\n" : "ra\n";
		if (p_options->option == 3)
			action = index ? "ra\n" : "rb\n";
		else if (p_options->option == 1)
			action = index ? "rrb\n" : "rra\n";
		else if (p_options->option == 2)
			action = index ? "rra\n" : "rrb\n";
		if (!(actions = (char*)malloc(1)))
			return (NULL);
		*actions = 0;
		while (p_options->nb_action--)
		{
			if (!p_options->nb_action)
			{
				action = "";
				if (p_options->option == 1)
					action = index ? "rrb" : "rra";
				else if (p_options->option == 2)
					action = index ? "rra\npb" : "rrb\npa";
				else if (p_options->option == 3)
					action = index ? "pb" : "pa";
			}
			tmp = actions;
			if (!(actions = ft_strjoin(actions, action)))
				return (NULL);
			free(tmp);
		}
	}
	else if (((pile->nb < p_options->pivot->nb && index) || (pile->nb > p_options->pivot->nb &&\
					!index)) && pile->next)
		action = "rb";
	else
		action = "pa";
	if (pile != first)
	{
		if (!(action = ft_strdup(action)))
			return (NULL);
		if (!index)
			action[1] = action[1] == 'b' ? 'a' : 'b';
	}
	else
		action = actions;
//	printf("action : |%s|\n", action);
	return (action);
}

static int	sort_sub_lst(t_stacks *stacks, char **operations,\
		t_pile *sorted, int index)
{
	t_pivot	*p_options;
	char	*action;
	t_pile	*pile;
	t_pile	*first;

//	printf("--------- SUB_LIST_SORT -----------\n");
	first = NULL;
	if (!(p_options = (t_pivot*)malloc(sizeof(t_pivot))))
		return (1);
	pile = index ? stacks->b_pile : stacks->a_pile;
	if (ft_lstlen(pile) < SUBLST_SIZE)
		return (little_list_sort(stacks, operations, index));
	if (!sorted)
		p_options->pivot = ft_lstgetlast(pile);
	else
		p_options->pivot = pivot_choice(pile, sorted);
	p_options->nb_action = choose_pivot_option(pile, p_options->pivot, &(p_options->option), index);
	p_options->pivot->p = 1;
	while (pile)
	{
//		printf("boucle\n");
//		ft_putlst(pile);
	printf("second\n");
		if (!(action = set_sort_action(pile, p_options, first, index)))
			return (1);
		if (append_actions(action, stacks, operations))
			return (1);
		free(action);
		if (pile == first)
			break ;
		if (!first && ((!ft_strcmp(action, "ra") && !index) || (!ft_strcmp(action, "rb") && index)))
			first = pile;
		pile = index ? stacks->b_pile : stacks->a_pile;
//		printf("-------------\n");
//		getchar();
	}
	if (index)
		if (append_actions("pa", stacks, operations))
			return (1);
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("--------- SUB_LIST_SORT DONE -----------\n");
//	getchar();
	return (0);
}

static int	isolate_sub_lst(t_stacks *stacks, char **operations, int *first)
{
//	printf("------ ISOLATE -------\n");
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
//	ft_putlst(stacks->a_pile);
//	ft_putlst(stacks->b_pile);
//	printf("----ISOLATE DONE-----\n");
//	getchar();
	return (0);
}

int			ft_quick_sort(t_stacks *stacks, char **operations, t_pile **sorted)
{
	int	*first;
	int end;

	first = NULL;
	end = ft_lstlen(stacks->a_pile) > SUBLST_SIZE ? 0 : 1;
//	printf("------ INIT ------\n");
	if (sort_sub_lst(stacks, operations, *sorted, 0))
		return (1);
//	printf("------ INIT DONE ------\n");
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
