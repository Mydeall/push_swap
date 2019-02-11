/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_rules_struct.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 12:56:44 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:06:39 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int			double_rules(char *pool, char *action, char **result)
{
	int	index;

	(void)pool;
	if (!ft_strcmp("ss", action))
		return (ss_rules(action, result));
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

t_rules		*make_rules_struct(void)
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
