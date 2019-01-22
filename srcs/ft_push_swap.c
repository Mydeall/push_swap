/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:57:38 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/22 15:28:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

int main(int ac, char *av[])
{
	t_stacks	stacks;
	char		*operations;
	t_oper_fcts	*fcts_tab;
	char		*tmp;
	t_pile		*sorted;

	stacks.a_pile = NULL;
	stacks.b_pile = NULL;
	sorted = NULL;
	operations = NULL;
	if (!(fcts_tab = make_struct()))
		return (1);
	if (!(stacks.a_pile = make_pile(ac, av, 0)))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	stacks.b_pile = NULL;
	if (ft_quick_sort(&stacks, &operations, fcts_tab, &sorted))
		return (1);
	printf("let's go again !\n");
	stacks.a_pile = make_pile(ac, av, 0);
	if (ft_quick_sort(&stacks, &operations, fcts_tab, &sorted))
		return (1);
	tmp = operations;
	if (!(operations = ft_simplifier(ft_strsplit(operations, '\n'))))
		return (1);
	free(tmp);
	write(1, operations, ft_strlen(operations));
	free(operations);
	return (0);
}
