/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:59:15 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/01 14:57:48 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static int	verif_operation(char *operation)
{
	int len;

	if (!operation)
		return (1);
	len = ft_strlen(operation);
	if ((len != 2 && len != 3) || !ft_strchr("spr", operation[0]))
		return (1);
	if (len == 2 && (!ft_strchr("ab", operation[1])\
				&& (operation[1] != operation[0] || operation[1] == 'p')))
		return (1);
	else if (len == 3 && (operation[1] != 'r'\
			|| operation[0] != 'r' || !ft_strchr("abr", operation[2])))
		return (1);
	return (0);
}

static void	verif_result(t_stacks *stacks)
{
	while (stacks->a_pile && stacks->a_pile->next &&\
			stacks->a_pile->nb < stacks->a_pile->next->nb)
		stacks->a_pile = stacks->a_pile->next;
	if (stacks->a_pile && !(stacks->a_pile->next) && !(stacks->b_pile))
		write(1, "OK\n", 3);
	else if (!stacks->a_pile && !stacks->b_pile)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

static int	apply_operations(t_list *operations, t_stacks *stacks,\
		int visualize)
{
	t_list	*current;

	if (visualize && stacks->a_pile)
		if (visualizer(stacks->a_pile, stacks->b_pile))
			return (1);
	current = operations;
	while (current)
	{
		if (action_applier((char*)current->content, stacks, visualize) == 1)
			return (1);
		current = current->next;
	}
	verif_result(stacks);
	if (operations)
		ft_listdel(&operations);
	ft_free_stacks(stacks);
	return (0);
}

int			read_input(t_list **operations, t_stacks *stacks)
{
	int		ret;
	t_list	*new;
	char	*line;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (verif_operation(line))
		{
			ft_free_stacks(stacks);
			write(2, "Error\n", 6);
			return (1);
		}
		if (!(new = ft_listnew(line, ft_strlen(line))))
			return (1);
		ft_listradd(operations, new);
	}
	return (0);
}

int			main(int ac, char *av[])
{
	t_list		*operations;
	int			visualize;
	t_stacks	*stacks;

	visualize = ft_strcmp(av[1], "-v") ? 0 : 1;
	stacks = NULL;
	operations = NULL;
	if (init_stacks(&stacks, ac, av, visualize))
	{
		ft_free_stacks(stacks);
		write(2, "Error\n", 6);
		return (1);
	}
	if (!stacks->a_pile && !stacks->b_pile)
		return (0);
	if (read_input(&operations, stacks))
		return (1);
	return (apply_operations(operations, stacks, visualize));
}
