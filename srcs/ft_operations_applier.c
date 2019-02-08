/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/08 14:55:26 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	take_decision(char *action, t_stacks *stacks, char **result,\
		int *pos)
{
	t_pool	*current;
	int		first;
	int		j;
	int		decision;

	current = stacks->pool;
	first = *pos ? 0 : 1;
	*pos = 0;
	decision = 0;
	while (current && (!decision || (decision == 1 && first)))
	{
		j = -1;
		while (++j < 5)
		{
			if (ft_strstr((stacks->rules_fcts[j]).action, current->action))
			{
				decision = stacks->rules_fcts[j].f(current->action,\
						action, result);
				break ;
			}
		}
		(*pos)++;
		current = current->next;
	}
	return (decision);
}

static int	manage_pool(char *action, t_stacks *stacks)
{
	int		decision;
	int		i;
	char	*result;
	t_pool	*node;

	result = NULL;
	i = 0;
	if ((decision = take_decision(action, stacks, &result, &i)) != 2)
	{
		i++;
		decision = take_decision(action, stacks, &result, &i);
	}
	if (decision == 1)
	{
		node = ft_poolgetpos(stacks->pool, i - 1);
		free(node->action);
		node->action = ft_strdup(result);
	}
	else if (decision != 2)
		if (ft_pooladd(&(stacks->pool), ft_poolnew(action)))
			return (1);
	if (decision == 2)
		ft_pooldel_node(&stacks->pool, i - 1);
	return (0);
}

int			append_actions(char *actions, t_stacks *stacks)
{
	char	**tab_op;
	int		i;

	if (!(tab_op = ft_strsplit(actions, '\n')))
		return (1);
	i = -1;
	while (tab_op[++i])
	{
		manage_pool(tab_op[i], stacks);
		if (action_applier(tab_op[i], stacks, 0))
			return (1);
		free(tab_op[i]);
	}
	free(tab_op);
	return (0);
}

int			action_applier(char *action, t_stacks *stacks,\
		int visualize)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if ((stacks->fcts_tab)[i].action == action[0])
		{
			((stacks->fcts_tab)[i]).f(action, &(stacks->a_pile),\
				&(stacks->b_pile));
			break ;
		}
	}
	if (visualize && visualizer(stacks->a_pile, stacks->b_pile))
		return (1);
	return (0);
}
