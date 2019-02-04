/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/04 19:28:24 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

/* actions :
0 : attendre (pool)
1 : merge (both)
2 : cancel (both)
3 : exec (pool) 
*/

static int	take_decision(char *action, t_stacks *stacks, char **result, int *pos)
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
			if (ft_strstr(((stacks->rules_fcts)[j]).action, current->action))
			{
				decision = stacks->rules_fcts[j].f(current->action, action, result);
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
//	printf("\n----------- MANAGE POOL -----------\n");
//	printf("action : %s\n", action);
	i = 0;
	if ((decision = take_decision(action, stacks, &result, &i)) != 2)
	{
		i++;
		decision = take_decision(action, stacks, &result, &i);
	}
	if (decision == 1 || decision == 2)
	{
//		printf("decision : %d\n", decision);
		ft_pooldel_node(&stacks->pool, i - 1);
	}
	if (decision != 2)
	{
		action = decision == 1 ? result : action;
		if (!(node = ft_poolnew(action)))
			return (1);
		ft_pooladd(&(stacks->pool), node);
	}
//	if (decision == 1 || decision == 2)
//		getchar();
//	printf("pool : \n");
//	ft_putpool(stacks->pool);
//	printf("\n--------- MANAGE POOL DONE --------\n");
	return (0);
}

int		append_actions(char *actions, t_stacks *stacks)
{
	char	**tab_op;
	int		i;

//	printf("\n-------------------- APPEND_ACTION ---------------------\n");
	if (!(tab_op = ft_strsplit(actions, '\n')))
		return (1);
	i = -1;
	while (tab_op[++i])
	{
		manage_pool(tab_op[i], stacks);
		if (action_applier(tab_op[i], stacks, 0))
			return (1);
	}
//	printf("------------------ APPEND_ACTION DONE ------------------\n");
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
