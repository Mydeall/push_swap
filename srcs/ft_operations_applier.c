/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operations_applier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 16:47:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 17:35:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int		operations_applier(t_stacks *stacks, int visualize)
{
	int			i;
	t_oper_fcts *fcts_tab;

	if(!(fcts_tab = make_struct()))
		return (1);
	while ((*stacks).operations)
	{
		i = -1;
		while (++i < 3)
			if (fcts_tab[i].operation == ((*stacks).operations)[0])
			{
				fcts_tab[i].f((*stacks).operations, a_pile((*stacks).a_pile),\
						b_pile((*stacks).b_pile));
				break;
			}
		operations++;
		if (visualize && visualizer(*a_pile((*stacks).a_pile),\
					*b_pile((*stacks).b_pile)))
			return (1);
	}
	return (0);
}
