/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:59:15 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/12 12:55:55 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	verif_operations(char **operations)
{
	int len;
	int i;

	if (!operations)
		return (1);
	i = -1;
	while (operations[++i])
	{
		len = ft_strlen(operations[i]);
		if ((len != 2 && len != 3) || !ft_strchr("spr", operations[i][0]))
			return (1);
		if ((ft_strchr("ab", operations[i][1]) ||\
					(operations[i][1] == operations[i][0] &&\
				operations[i][1] != 'p')) && len == 2)
			continue;
		else if (len == 3 && operations[i][1] == 'r' &&\
				operations[i][0] == 'r' && ft_strchr("abr", operations[i][2]))
			continue;
		else
			return (1);
	}
	return (0);
}

static void	verif_result(t_stacks *stacks)
{
	while (stacks->a_pile && stacks->a_pile->next &&\
			stacks->a_pile->nb < stacks->a_pile->next->nb)
		stacks->a_pile = stacks->a_pile->next;
	if (stacks->a_pile && !(stacks->a_pile->next) && !(stacks->b_pile))
		write(1, "OK\n", 3);
	else if (!stacks->a_pile && !stacks->b_pile)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
}

static int	apply_operations(char **operations, int ac,\
		char *av[], int visualize)
{
	t_stacks	*stacks;
	int			i;

	stacks = NULL;
	if (init_stacks(&stacks, ac, av, visualize) ||\
			verif_operations(operations))
	{
		ft_free_stacks(stacks);
		write(2, "Error\n", 6);
		return (1);
	}
	if (visualize && stacks->a_pile)
		if (visualizer(stacks->a_pile, stacks->b_pile))
			return (1);
	i = -1;
	while (operations[++i])
		if (action_applier(operations[i], stacks, visualize) == 1)
			return (1);
	verif_result(stacks);
	ft_freetab(operations);
	ft_free_stacks(stacks);
	return (0);
}

int			main(int ac, char *av[])
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	char	**operations;
	char	*tmp;
	int		visualize;

	visualize = ft_strcmp(av[1], "-v") ? 0 : 1;
	if (!(operations = (char**)malloc(sizeof(char*))) ||
			!(*operations = (char*)malloc(1)))
		return (1);
	while ((ret = read(0, buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (1);
		buff[ret] = 0;
		tmp = *operations;
		if (!(*operations = ft_strjoin(*operations, buff)))
			return (1);
		ft_strdel(&tmp);
	}
	tmp = *operations;
	if (!(operations = ft_strsplit(*operations, '\n')))
		return (1);
	ft_strdel(&tmp);
	return (apply_operations(operations, ac, av, visualize));
}
