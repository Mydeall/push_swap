/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/31 17:17:16 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

void	del_pool(t_pool **pool, int pos)
{
	t_pile *prev;
	t_pile *current;
	int		i;

	current = *lst;
	prev = NULL;
	i = -1;
	while (++i < pos)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = current->next;
	else
		*pool = current->next;
	free(current->action);
	free(current);
}

static t_pool	*pool_new(char *action)
{
	t_pile	*new;

	if (!(new = (t_pile*)malloc(sizeof(t_pile) * 1)))
		return (NULL);
	new->action = ft_strdup(action);
	new->next = NULL;
	return (new);
}

static void	add_pool(t_pool **pool, t_pool *pool)
{
	t_pool	*tmp;

	if (pool)
	{
		tmp = *pool;
		new->next = tmp;
		*pool = new;
	}
}

static char	*determine_action(int decision, char *action, t_pool **pool, int pos)
{
	t_pool	*new;
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!decision)
	{
		if (!(new = pool_new(ft_strdup(action))))
			return (NULL);
		add_pool(pool, new);
	}
	else if (decision == 1)
	{
		del_pool(pos);
		result = ft_strdup(action);
		result[ft_strlen(action) - 1] = action[0];
	}
	else if (decision == 2)
		del_pool(pos);
	else if (decision == 3)
	{
		new = *pool;
		i = -1;
		while (++i < pos)
			new = new->next;
		result = ft_strdup(new->action);
		del_pool(pos);
	}
	return (result);
}

/* actions :
0 : attendre (pool)
1 : merge (both)
2 : cancel (both)
3 : exec (pool) 
*/

static int	apply_decision(char *action, t_stacks stacks, char **operations)
{
	char	*tmp;

	action_applier(result, stacks, 0);
	tmp = *operations;
	if (!(*operations = ft_strjoinarg(3, *operations, result, "\n")))
		return (1);
	free(tmp);
	free(action);
	return (0);
}

static int	evaluate_action(char *action, t_pool *pool,\
		t_stacks *stacks, char **operations)
{
	int					decision;
	t_pool				*current;
	static t_oper_fcts	*rules_fcts;
	int					i;
	int					j;
	char 				*result;

	current = pool;
	decision = 0;
	if (!rules_fcts)
		rules_fcts = make_rules_struct();
	i = 0;
	while(current && (decision == 0 || decision == 3))
	{
		j = -1;
		while (++j < 4)
			if (ft_strstr(rules_fcts[j].action, action))
			{
				decision = rules_fcts[j].f(action, current->action);
				break ;
			}
		if (decision != 0)
		{
			if (!(result = determine_action(decision, action, &pool, i)))
				return (1);
			if (!(apply_decision(result, stacks, operations)));
				return (1);
		}
		free(result);
		i++;
		current = current->next;
	}
	if (!current && !decision)
	{
		if (!(determine_action(decision, action, &pool, 0)))
			return (1);
		if (!(apply_decision(result, stacks, operations)));
			return (1);
	}
}

int		append_actions(char *actions, t_stacks *stacks,\
		char **operations)
{
	char	**tab_op;
	static t_pool	*pool;
	int		i;

	//	printf("actions append : |%s|\n", actions);
	//	ft_putlst(stacks->a_pile);
	//	ft_putlst(stacks->b_pile);
	//	getchar();
	if (!(tab_op = ft_strsplit(actions, '\n')))
		return (1);
	i = -1;
	while (tab_op[++i])
		evaluate_action(tab_op[i], pool);
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
