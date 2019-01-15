/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:17:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/15 15:34:41 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

t_pile	*make_pile(int ac, char *av[], int visualize)
{
	int		i;
	int		j;
	t_pile	*a_pile;

// VERIF SI PAS DE DOUBLON	
	a_pile = NULL;
	i = -1;
	while (++i < ac - (1 + visualize))
	{
		j = -1;
		while (av[i + (1 + visualize)][++j])
		{
			if (ft_isdigit(av[i + (1 + visualize)][j]) != 1)
				return (NULL);
		}
		ft_lstaddend(&a_pile, ft_lstnew(ft_atoi(av[i + (1 + visualize)])));
	}
	return (a_pile);
}
