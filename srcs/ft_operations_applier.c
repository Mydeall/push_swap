/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/01 16:25:36 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static void	ft_lstdel_node(t_list **pool, int pos)
{
	t_list	*prev;
	t_list	*current;
	int		i;

	current = *pool;
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
	free(current->content);
	free(current);
}

//----------------------------------------------------------
// listnew

static char	*determine_action(int decision, char *action, t_list **pool, int pos)
{
	t_list	*new;
	char	*result;
	int		i;

	printf("\n---------DETERMINE ACTION--------\n");
	printf("decision : %d\n", decision);
	if (!decision)
	{
		if (!(new = ft_listnew(action, ft_strlen(action) + 1)))
			return (NULL);
		ft_listadd(pool, new);
		if (!(result = ft_strdup("")))
			return (NULL);
	}
	else if (decision == 1)
	{
		ft_lstdel_node(pool, pos);
		if (!(result = ft_strdup(action)))
			return (NULL);
		printf("result[ft_strlen(action) - 1] : %c\n", result[ft_strlen(action) - 1]);
		result[ft_strlen(action) - 1] = action[0];
	}
	else if (decision == 2)
	{
		ft_lstdel_node(pool, pos);
		if (!(result = ft_strdup("")))
			return (NULL);
	}
	else
	{
		printf("else\n");
		new = *pool;
		i = -1;
		while (++i < pos)
			new = new->next;
		if (!(result = ft_strdup(new->content)))
			return (NULL);
		ft_lstdel_node(pool, pos);
	}
	printf("pool : \n");
	ft_putlst_str(*pool);
	printf("action to exec : |%s|\n", result);
	printf("------DETERMINE DONE----------\n");
	getchar();
	return (result);
}

/* actions :
0 : attendre (pool)
1 : merge (both)
2 : cancel (both)
3 : exec (pool) 
*/

static int	apply_decision(char *action, t_stacks *stacks, char **operations)
{
	char	*tmp;

	printf("\n-------APPLY DECISION----------\n");
	printf("action : |%s|\n", action);
	action_applier(action, stacks, 0);
	tmp = *operations;
	if (!(*operations = ft_strjoinarg(3, *operations, action, "\n")))
		return (1);
	free(tmp);
	printf("-------- APPLY DECISION DONE ---------\n");
	getchar();
	return (0);
}

static int	evaluate_action(char *action,\
		t_stacks *stacks, char **operations)
{
	int					decision;
	t_list				*current;
	int					i;
	int					j;
	char 				*result;

	current = stacks->pool;
	decision = 0;
	i = 0;
	printf("\n-------EVALUATION-------\n");
	printf("action : %s\n", action);
	printf("pool : \n");
	ft_putlst_str(stacks->pool);
	while (current && (decision == 0 || decision == 3))
	{
		j = -1;
		printf("pool : |%s|\n", current->content);
		while (++j < 4)
		{
			printf("fct compared : %s\n", ((stacks->rules_fcts)[j]).action);
			if (ft_strstr(((stacks->rules_fcts)[j]).action, current->content))
			{
				printf("fct matched : %s\n", stacks->rules_fcts[j].action);
				decision = stacks->rules_fcts[j].f(current->content, action);
				printf("RULED ! decision : %d\n", decision);
				break ;
			}
		}
		if (decision != 0)
		{
			if (!(result = determine_action(decision, action, &(stacks->pool), i)))
				return (1);
			if (apply_decision(result, stacks, operations))
				return (1);
			free(result);
		}
		i++;
		current = current->next;
	}
	printf("\n\n\n\n\n\nEND evaluate boucle --> current : %p | decsion : %d\n", current, decision);
	if (!current && (!decision || decision == 3))
	{
		if (!(result = determine_action(0, action, &(stacks->pool), 0)))
			return (1);
		if (!(apply_decision(result, stacks, operations)))
			return (1);
	}
	free(result);
	printf("pool : \n");
	ft_putlst_str(stacks->pool);
	printf("EVALUATION DONE\n");
	getchar();
	return (0);
}

int		append_actions(char *actions, t_stacks *stacks,\
		char **operations)
{
	char	**tab_op;
	int		i;

	printf("\n---------APPEND_ACTION----------\n");
	printf("actions append : |%s|\n", actions);
	if (!(tab_op = ft_strsplit(actions, '\n')))
		return (1);
	i = -1;
	while (tab_op[++i])
		evaluate_action(tab_op[i], stacks, operations);
	ft_putlst(stacks->a_pile);
	ft_putlst(stacks->b_pile);
	printf("----------------------------- APPEND_ACTION DONE -----------------\n");
	getchar();
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
