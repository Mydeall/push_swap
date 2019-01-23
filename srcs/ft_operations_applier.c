/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/23 16:22:47 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int		append_actions(char *actions, t_stacks *stacks,\
		char **operations)
{
	char	**tab_op;
	char	*tmp;

	if (!(tab_op = ft_strsplit(actions, '\n')))
		return (1);
	while (*tab_op)
	{
		action_applier(*tab_op, stacks, 0);
		tab_op++;
	}
	tmp = *operations;
	if (!(*operations = ft_strjoinarg(3, *operations, actions, "\n")))
		return (1);
	free(tmp);
	return (0);
}

int		action_applier(char *action, t_stacks *stacks,\
		int visualize)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((stacks->fcts_tab)[i].action == action[0])
		{
			((stacks->fcts_tab)[i]).f(action, &(stacks->a_pile), &(stacks->b_pile));
			break ;
		}
	}
	if (visualize && visualizer(stacks->a_pile,	stacks->b_pile))
		return (1);
	return (0);
}
