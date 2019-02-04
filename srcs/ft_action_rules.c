/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:36:41 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/04 18:57:38 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* actions :
0 : attendre (pool)
1 : merge (both)
2 : cancel (both)
3 : exec (pool) 
*/

#include "push_swap.h"
#include "libft.h"

int		r_rules(char *pool, char *action, char **result)
{
	int	index;

	index = pool[1] == 'a' ? 0 : 1;
	if ((ft_strstr("rb|rrr", action) && !index) ||\
			(ft_strstr("ra|rrr", action) && index))
	{
		if (!index)
			*result = !ft_strcmp("rb", action) ? "rr" : "rrb";
		else
			*result = !ft_strcmp("ra", action) ? "rr" : "rra";
		return (1);
	}
	else if ((ft_strstr("sb|rrb|rr", action) && !index) ||\
			(ft_strstr("sa|rra|rr", action) && index))
		return (0);
	else if ((!ft_strcmp("rra", action) && !index) ||\
			(!ft_strcmp("rrb", action) && index))
		return (2);
	else
		return (3);
}

int		rr_rules(char *pool, char *action, char **result)
{
	int	index;

	index = pool[2] == 'a' ? 0 : 1;
	if ((ft_strstr("sb|rb|rrr", action) && !index) ||\
			(ft_strstr("sa|ra|rrr", action) && index))
		return (0);
	else if ((!ft_strcmp("ra", action) && !index) ||\
			(!ft_strcmp("rb", action) && index))
		return (2);
	else if ((ft_strstr("rrb|rr", action) && !index) ||\
			(ft_strstr("rra|rr", action) && index))
	{
		if (!index)
			*result = !ft_strcmp("rrb", action) ? "rrr" : "rb";
		else
			*result = !ft_strcmp("rra", action) ? "rrr" : "ra";
		return (1);
	}
	else
		return (3);
}

int		s_rules(char *pool, char *action, char **result)
{
	int	index;

	index = pool[1] == 'a' ? 0 : 1;
	if ((ft_strstr("rrb|rb", action) && !index) ||\
			(ft_strstr("rra|ra", action) && index))
		return (0);
	else if ((ft_strstr("sb|ss", action) && !index) ||\
			(ft_strstr("sa|ss", action) && index))
	{
		if (!index)
			*result = !ft_strcmp("sb", action) ? "ss" : "sa";
		else
			*result = !ft_strcmp("sa", action) ? "ss" : "sb";
		return (1);
	}
	else if ((!ft_strcmp("sa", action) && !index) ||\
			(!ft_strcmp("sb", action) && index))
		return (2);
	else
		return (3);
}

int		p_rules(char *pool, char *action, char **result)
{
	int	index;

	(void)result;
	index = pool[1] == 'a' ? 0 : 1;
	if ((!ft_strcmp("pb", action) && !index) ||\
			(!ft_strcmp("pa", action) && index))
		return (2);
	else
		return (3);
}

static int	ss_rules(char *action, char **result)
{
	if (ft_strstr("sb|sa", action))
	{
		*result = !ft_strcmp("sb", action) ? "sa" : "sb";
		return (1); 
	}
	else if (!ft_strcmp("ss", action))
		return (2); 
	else
		return (3); 
}

int		double_rules(char *pool, char *action, char **result)
{
	int	index;

	(void)pool;
	if (!ft_strcmp("ss", action))
		return (ss_rules(action, result));
	else
	{
		index = ft_strlen(action) == 2 ? 0 : 1;
		if (ft_strstr("ra|rb|rr", action) && !index)
			return (0);
		else if ((ft_strstr("rra|rrb", action) && !index) ||\
				(ft_strstr("ra|rb", action) && index))
		{
			if (!index)
				*result = !ft_strcmp("rra", action) ? "rb" : "ra";
			else
				*result = !ft_strcmp("ra", action) ? "rrb" : "rra";
			return (1);
		}
		else if (ft_strstr("rra|rrb|rrr", action) && index)
			return (0);
		else if ((!ft_strcmp("rrr", action) && !index) ||\
				(!ft_strcmp("rr", action) && index))
			return (2);
		else
			return (3);
	}
}

t_rules	*make_rules_struct(void)
{
	t_rules *rules_fcts;

	if (!(rules_fcts = (t_rules*)malloc(sizeof(t_rules) * 5)))
		return (NULL);
	rules_fcts[0].action = "rrr|rr|ss";
	rules_fcts[0].f = &double_rules;
	rules_fcts[1].action = "sa|sb";
	rules_fcts[1].f = &s_rules;
	rules_fcts[2].action = "pa|pb";
	rules_fcts[2].f = &p_rules;
	rules_fcts[3].action = "ra|rb";
	rules_fcts[3].f = &r_rules;
	rules_fcts[4].action = "rra|rrb";
	rules_fcts[4].f = &rr_rules;
	return (rules_fcts);
}
