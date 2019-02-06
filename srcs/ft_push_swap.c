/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:57:38 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/06 15:02:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	main(int ac, char *av[])
{
	t_stacks	stacks;
	char		*operations;
	t_pile		*sorted;

	stacks.rr[0] = 0;
	stacks.rr[1] = 0;
	stacks.rrr[0] = 0;
	stacks.rrr[1] = 0;
	operations = NULL;
	stacks.b_pile = NULL;
	stacks.pool = NULL;
	if (!(stacks.fcts_tab = make_struct()) ||
			!(stacks.rules_fcts = make_rules_struct()))
		return (1);
	if (make_pile(&(stacks.a_pile), ac, av, 0) ||\
			make_pile(&sorted, ac, av, 0))
	{
		write(1, "Error\n", 6);
		ft_free_stacks(&stacks);
		return (1);
	}
	if (ft_lstlen(stacks.a_pile) == 0 || ft_lstlen(stacks.a_pile) == 1)
	{
		ft_free_stacks(&stacks);
		return (0);
	}
	sorted = ft_sort(sorted);
	if (ft_quick_sort(&stacks, &sorted, &operations))
		return (1);
	write(1, operations, ft_strlen(operations));
	ft_free_stacks(&stacks);
	if (operations)
		free(operations);
	ft_freelst(sorted);
	return (0);
}
