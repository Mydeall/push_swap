/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_pile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 15:17:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/08 14:38:14 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

t_stacks	*init_stacks(t_stacks *stacks, int ac, char **av, int visualize)
{
	if (!(stacks = (t_stacks*)malloc(sizeof(t_stacks))))
		return (NULL);
	if (!(stacks->fcts_tab = make_struct()))
		return (NULL);
	stacks->b_pile = NULL;
	stacks->a_pile = NULL;
	stacks->pool = NULL;
	stacks->rules_fcts = NULL;
	stacks->rr[0] = 0;
	stacks->rr[1] = 0;
	stacks->rrr[0] = 0;
	stacks->rrr[1] = 0;
	if (make_pile(&(stacks->a_pile), ac, av, visualize))
		return (NULL);
	if (!(stacks->rules_fcts = make_rules_struct()))
		return (NULL);
	return (stacks);
}

void		ft_free_stacks(t_stacks *stacks)
{
	if (stacks->a_pile)
		ft_freelst(stacks->a_pile);
	if (stacks->b_pile)
		ft_freelst(stacks->b_pile);
	if (stacks->fcts_tab)
		free(stacks->fcts_tab);
	if (stacks->rules_fcts)
		free(stacks->rules_fcts);
	free(stacks);
}

static char	**split_string(int *ac, char *av[])
{
	char	**tmp;

	tmp = av;
	if (!(av = ft_strsplit(av[0], ' ')))
		return (NULL);
	*ac = 0;
	while (av[*ac])
		(*ac)++;
	return (av);
}

static int	append_args(int ac, char **av, t_pile **a_pile)
{
	int		i;
	int		j;
	int		nb;
	t_pile	*new;

	i = -1;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) != 1 && av[i][j] != '-' &&\
					av[i][j] != '+')
				return (1);
		}
		if (ft_strlen(av[i]) > 11 || ft_atoi(av[i]) > 2147483647 ||\
				ft_atoi(av[i]) < -2147483648)
			return (1);
		nb = ft_atoi(av[i]);
		if (ft_lstgetpos(*a_pile, nb) != -1 ||\
				!(new = ft_lstnew(ft_atoi(av[i]))))
			return (1);
		ft_lstaddend(a_pile, new);
	}
	return (0);
}

int			make_pile(t_pile **a_pile, int ac, char *av[], int visualize)
{
	int		malloc;
	int		error;

	*a_pile = NULL;
	av += 1 + visualize;
	ac -= 1 + visualize;
	malloc = 0;
	if (ac == 1)
	{
		if (!(av = split_string(&ac, av)))
			return (1);
		malloc = 1;
	}
	error = append_args(ac, av, a_pile);
	if (malloc)
		ft_freetab(av);
	if (error)
		return (1);
	return (0);
}
