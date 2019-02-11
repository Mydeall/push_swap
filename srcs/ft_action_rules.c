/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:36:41 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:06:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
