/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:56:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:09:35 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <time.h>

static int	display_value(int value, int max, int min)
{
	char	*str;

	if (!(str = (char*)malloc(value - min + 2)))
		return (1);
	str = ft_memset(str, '|', value - min + 1);
	str[value - min + 1] = 0;
	ft_printf("%*s", max, str);
	free(str);
	return (0);
}

static void	display_piles(t_pile *a_pile, t_pile *b_pile, int max, int min)
{
	while (a_pile || b_pile)
	{
		if (a_pile)
		{
			display_value(a_pile->nb, max, min);
			a_pile = a_pile->next;
		}
		else
			ft_printf("%*s", max, "");
		ft_printf(" ");
		if (b_pile)
		{
			display_value(b_pile->nb, max, min);
			b_pile = b_pile->next;
		}
		else
			ft_printf("%*s", max, "");
		ft_printf("\n");
	}
}

int			visualizer(t_pile *a_pile, t_pile *b_pile)
{
	int		max;
	int		min;

	min = a_pile ? a_pile->nb : b_pile->nb;
	max = a_pile ? a_pile->nb : b_pile->nb;
	if ((a_pile && ft_lst_opposites(a_pile, &min, &max)) ||\
			(b_pile && ft_lst_opposites(b_pile, &min, &max)))
		return (1);
	max += ft_abs(min) + 1;
	usleep(100000);
	system("clear");
	display_piles(a_pile, b_pile, max, min);
	return (0);
}
