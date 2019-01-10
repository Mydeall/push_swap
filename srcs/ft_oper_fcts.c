/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_oper_fcts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:55:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/10 17:52:21 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		swap(char *operation, int **a_pile, int **b_pile, int (*size)[2])
{
	int **pile;

	(void)size;
	if (operation[1] == 'a')
		pile = a_pile;
	else
		pile = b_pile;
	ft_swap(*pile, (*pile)++);
	if (operation[1] == 's')
		ft_swap(*a_pile, (*a_pile)++);
}

void		push(char *operation, int **a_pile, int **b_pile, int (*size)[2])
{
	if (operation[1] == 'a')
	{
		**a_pile = **b_pile;
		(*size)[0]++;
		(*size)[1]--;
	}
	else
	{
		**b_pile = **a_pile;
		(*size)[0]--;
		(*size)[1]++;
	}
}

static void	rotation(int **pile, int size, int side)
{
	int i;
	int tmp;
	int zero;

	i = -1;
	zero = (*pile)[0];
	while (++i < size)
	{
		tmp = (*pile)[i];
		if (i + side < 0)
		   (*pile)[i] = (*pile)[size + side];
		else if (i + side < size)
			(*pile)[i] = zero;
		else
		{
			if (side > 0)
				(*pile)[i] = (*pile)[i + 1];
			else
				(*pile)[i] = tmp;
 		}	
	}
}

void		rotate(char *operation, int **a_pile, int **b_pile, int (*size)[2])
{
	int side;

	operation = ft_strlen(operation) == 2 ? operation + 1 : operation + 2;
	side = ft_strlen(operation) == 2 ? 1 : -1;
	if (*operation != 'b')
		rotation(a_pile, (*size)[0], side);
	if (*operation != 'a')
		rotation(b_pile, (*size)[1], side);
}

t_oper_fcts	*make_struct(void)
{
	t_oper_fcts *fcts_tab;

	if (!(fcts_tab = (t_oper_fcts*)malloc(sizeof(t_oper_fcts) * 3)))
		return (NULL);
	fcts_tab[0].operation = 's';
	fcts_tab[0].f = &swap;
	fcts_tab[1].operation = 'p';
	fcts_tab[1].f = &swap;
	fcts_tab[2].operation = 'r';
	fcts_tab[2].f = &swap;
	return (fcts_tab);
}
