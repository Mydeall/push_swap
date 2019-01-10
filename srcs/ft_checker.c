/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:48:18 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/10 17:28:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*make_pile(int ac, char *av[])
{
	int i;
	int j;
	int	*a_pile;
	
	if (!(a_pile = (int*)malloc(sizeof(int) * (ac - 1))))
		return (NULL);
	i = -1;
	while (++i < ac - 1)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] != 1)
				return (NULL);
		a_pile[i] = ft_atoi(*av);
	}
	return (a_pile);
}

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
		if ((ft_strchr("ab", operations[i][1]) || (operations[i][1] == operations[i][0] &&\
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

static int apply_operation(char **operations, int **a_pile, int **b_pile, int (*size)[2])
{
	int i;
	t_oper_fcts *fcts_tab;

	if(!(fcts_tab = make_struct()))
		return (1);
	i = -1;
	while (*operations)
	{
		while (++i < 3)
			if (fcts_tab[i].operation == (*operations)[0])
			{
				fcts_tab[i].f(*operations, a_pile, b_pile, size);
				break;
			}
		(*operations)++;
	}
	return (0);
}

static int	operations_applier(char **operations, int *a_pile, int size)
{
	int			i;
	int			*b_pile;
	int			tab_size[2];

	if (verif_operations(operations) ||
			!(b_pile = (int*)malloc(sizeof(int) * size))) 
		return (1);
	tab_size[0] = size;
	tab_size[1] = 0;
	if (apply_operation(operations, &a_pile, &b_pile, &tab_size))
		return (1);
	i = -1;
	while (++i < size - 1)
		if (a_pile[i] <= a_pile[i + 1])
		{
			write(1, "KO", 2);
			break;
		}
	if (i == size - 2)
		write(1, "OK", 2);
	return (0);
}

int	main(int ac, char *av[])
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	int		*a_pile;
	char	**operations;
	char	*tmp;

	if (!(a_pile = make_pile(ac, av)) || 
			!(operations = (char**)malloc(sizeof(char*))) ||
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
	operations_applier(operations, a_pile, ac - 1);
	return (0);
}
