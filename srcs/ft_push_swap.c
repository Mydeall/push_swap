/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:57:38 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/08 14:37:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int	main(int ac, char *av[])
{
	t_stacks	*stacks;
	char		*operations;
	t_pile		*sorted;

	if (!(stacks = init_stacks(stacks, ac, av, 0)) ||\
			make_pile(&sorted, ac, av, 0))
	{
		write(2, "Error\n", 6);
		ft_free_stacks(stacks);
		return (1);
	}
	if (ft_lstlen(stacks->a_pile) == 0 || ft_lstlen(stacks->a_pile) == 1)
	{
		ft_free_stacks(stacks);
		return (0);
	}
	sorted = ft_sort(sorted);
	if (ft_quick_sort(stacks, &sorted, &operations))
		return (1);
	write(1, operations, ft_strlen(operations));
	ft_free_stacks(stacks);
	ft_strdel(&operations);
	ft_freelst(sorted);
	return (0);
}
