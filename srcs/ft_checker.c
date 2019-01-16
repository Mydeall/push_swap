/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:48:18 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 16:54:53 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int		verif_operations(char **operations)
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
		else if (len == 3 && operations[i][1] == 'r' && operations[i][0] == 'r' &&\
				ft_strchr("abr", operations[i][2]))
			continue;
		else
			return (1);
	}
	return (0);
}

static int	verif_result(char **operations, int ac, char *av[], int visualize)
{
	t_pile	*b_pile;
	t_pile	*a_pile;

	if (!(a_pile = make_pile(ac, av, visualize)) || verif_operations(operations))
	{
		write(1, "Error\n", 6);
		return (1);
	}
	b_pile = NULL;
	if (operations_applier(operations, &a_pile, &b_pile, visualize))
		return (1);
	while (a_pile->next && a_pile->nb < (a_pile->next)->nb )
		a_pile = a_pile->next;
	if (!(a_pile->next) && !(b_pile))
		write(1, "OK", 2);
	else
		write(1, "KO", 2);
	return (0);
}

int	main(int ac, char *av[])
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
	ft_putstrtab(operations);
	operations_applier(operations, ac, av, visualize);
	return (0);
}
