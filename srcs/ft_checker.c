/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 11:48:18 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/14 14:38:10 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static t_pile	*make_pile(int ac, char *av[])
{
	int		i;
	int		j;
	t_pile	*a_pile;
	
	a_pile = NULL;
	i = -1;
	while (++i < ac - 1)
	{
		j = -1;
		while (av[i + 1][++j])
		{
			if (ft_isdigit(av[i + 1][j]) != 1)
				return (NULL);
		}
		ft_lstaddend(&a_pile, ft_lstnew(ft_atoi(av[i + 1])));
	}
	return (a_pile);
}

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



static int		apply_operation(char **operations, t_pile **a_pile, t_pile **b_pile)
{
	int			i;
	t_oper_fcts *fcts_tab;

	if(!(fcts_tab = make_struct()))
		return (1);
	while (*operations)
	{
		printf("operation to apply : %s\n", *operations);
		i = -1;
		while (++i < 3)
			if (fcts_tab[i].operation == (*operations)[0])
			{
				fcts_tab[i].f(*operations, a_pile, b_pile);
				ft_putlst(*a_pile);
				ft_putlst(*b_pile);
				break;
			}
		operations++;
		if (visualizer(*a_pile, *b_pile))
			return (1);
	}
	return (0);
}

static int	operations_applier(char **operations, t_pile *a_pile)
{
	t_pile		*b_pile;

	if (verif_operations(operations)) 
		return (1);
	b_pile = NULL;
	if (apply_operation(operations, &a_pile, &b_pile))
		return (1);
	printf("applied\n");
	ft_putlst(a_pile);
	while (a_pile->next)
	{
		if (a_pile->nb > (a_pile->next)->nb || b_pile)
		{
			write(1, "KO", 2);
			break;
		}
		a_pile = a_pile->next;
	}
	if (a_pile->next == NULL)
		write(1, "OK", 2);
	return (0);
}

int	main(int ac, char *av[])
{
	int		ret;
	char	buff[BUFF_SIZE + 1];
	t_pile	*a_pile;
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
	ft_putstrtab(operations);
	operations_applier(operations, a_pile);
	return (0);
}
