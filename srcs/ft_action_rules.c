/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:36:41 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/31 17:07:24 by ccepre           ###   ########.fr       */
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

int	r_action(char *pool, char *action)
{
	int	index;

	index = pool[1] == 'a' ? 0 : 1;
	if ((ft_strstr("sb|rrb", action) && !index) ||\
			(ft_strstr("sa|rra", action) && index))
		return (0);
	else if ((!ft_strcmp("rb", action) && !index) ||\
			(!ft_strcmp("rb", action) && !index))
		return (1);
	else if ((!ft_strcmp("rra", action) && !index) ||\
			(!ft_strcmp("rrb", action) && index))
		return (2);
	else
		return (3);
}

int	rr_action(char *pool, char *action)
{
	int	index;

	index = pool[2] == 'a' ? 0 : 1;
	if ((ft_strstr("sb|rb", action) && !index) ||\
			(ft_strstr("sa|ra", action) && index))
		return (0);
	else if ((!ft_strcmp("rrb", action) && !index) ||\
			(!ft_strcmp("rrb", action) && !index))
		return (1);
	else if ((!ft_strcmp("ra", action) && !index) ||\
			(!ft_strcmp("rb", action) && index))
		return (2);
	else
		return (3);
}

int	s_action(char *pool, char *action)
{
	int	index;

	index = pool[1] == 'a' ? 0 : 1;
	if ((ft_strstr("rrb|rb", action) && !index) ||\
			(ft_strstr("rra|ra", action) && index))
		return (0);
	else if ((!ft_strcmp("sb", action) && !index) ||\
			(!ft_strcmp("sb", action) && !index))
		return (1);
	else if ((!ft_strcmp("sa", action) && !index) ||\
			(!ft_strcmp("sb", action) && index))
		return (2);
	else
		return (3);
}

int	p_action(char *pool, char *action)
{
	int	index;

	index = pool[1] == 'a' ? 0 : 1;
	if ((ft_strstr("sb|rrb|rb", action) && !index) ||\
			(ft_strstr("sa|rra|ra", action) && index))
		return (0);
	else if ((!ft_strcmp("pb", action) && !index) ||\
			(!ft_strcmp("pa", action) && index))
		return (2);
	else
		return (3);
}

t_rules	*make_rules_struct(void)
{
	t_rules *rules_fcts;

	if (!(rules_fcts = (t_rules*)malloc(sizeof(t_rules) * 3)))
		return (NULL);
	rules_fcts[0].action = "sa|sb";
	rules_fcts[0].f = &s_rule;
	rules_fcts[1].action = "pa|pb";
	rules_fcts[1].f = &p_rules;
	rules_fcts[2].action = "ra|rb";
	rules_fcts[2].f = &r_rules;
	rules_fcts[2].action = "rra|rrb";
	rules_fcts[2].f = &rr_rules;
	return (rules_fcts);
}
