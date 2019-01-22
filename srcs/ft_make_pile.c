/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:17:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/21 15:35:22 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

char	**split_string(int *ac, char *av[])
{
	char **tmp;

	tmp = av;
	if (!(av = ft_strsplit(av[0], ' ')))
		return (NULL);
//	ft_putstrtab(av);
	*ac = 0;
	while (av[*ac])
		(*ac)++;
	return(av);
}

t_pile	*make_pile(int ac, char *av[], int visualize)
{
	int		i;
	int		j;
	t_pile	*a_pile;

// VERIF SI PAS DE DOUBLON ou si tiennent pas dans un int
	a_pile = NULL;
	i = -1;
	av += 1 + visualize;
	ac -= 1 + visualize;
	if (ac == 1)
		if (!(av = split_string(&ac, av)))
			return (NULL);
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) != 1 && av[i][j] != '-' &&\
				   	av[i][j] != '+')
				return (NULL);
		}
		ft_lstaddend(&a_pile, ft_lstnew(ft_atoi(av[i])));
	}
//	ft_putlst(a_pile);
	return (a_pile);
}
