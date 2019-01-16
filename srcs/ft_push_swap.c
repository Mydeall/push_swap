/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:57:38 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 17:09:30 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int main(int ac, char *av[])
{
	t_stacks	stacks;

	if (!(stacks.a_pile = (t_pile*)malloc(sizeof(t_pile))) ||\
			(!(stacks.b_pile = (t_pile*)malloc(sizeof(t_pile)))))
		return (1);
	if (!(stacks.a_pile = make_pile(ac, av, 0)))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	stacks.b_pile = NULL;
	if (ft_quick_sort(&stacks))
		return (1);
	write(1, stacks.operations, ft_strlen(stacks.operations))
	free(stacks.operations);
	return (0);
}
