/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:56:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/31 12:24:03 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"
#include <time.h>

int			ft_lst_opposites(t_pile *pile, int *min, int *max)
{
	t_pile *current;

	if (!(pile))
		return (1);
	current = pile;
	while (current)
	{
		if (max && current->nb > *max)
			*max = current->nb;
		else if (min && current->nb < *min)
			*min = current->nb;
		current = current->next;
	}
	return (0);
}

static int	display_value(int value, int max, int min)
{
	char	*str;

	if (!(str = (char*)malloc(value - min + 2))) 
		return (1);
	str = ft_memset(str, '|', value - min + 1);
	str[value - min + 1] = 0;
	printf("%*s", max, str);
	free(str);
	return (0);
}

int			visualizer(t_pile *a_pile, t_pile *b_pile)
{
	int		max;
	int		min;
	int		len_max;
	int		len_a;
	int		len_b;

	min = a_pile ? a_pile->nb : b_pile->nb;
	max = a_pile ? a_pile->nb : b_pile->nb;
	if ((a_pile && ft_lst_opposites(a_pile, &min, &max)) ||\
			(b_pile && ft_lst_opposites(b_pile, &min, &max)))
		return (1);
	max += ft_abs(min) + 1;
	len_a = ft_lstlen(a_pile);
	len_b = ft_lstlen(b_pile);
	len_max = len_a + len_b;
	usleep(500000);
	system("clear");
	while (len_max)
	{
		if (len_a == len_max)
		{
			display_value(a_pile->nb, max, min);
			a_pile = a_pile->next;
			len_a--;
		}
		else
			printf("%*s", max, "");
		printf(" ");
		if (len_b == len_max)
		{
			display_value(b_pile->nb, max, min);
			b_pile = b_pile->next;
			len_b--;
		}
		else
			printf("%*s", max, "");
		printf("\n");
		len_max--;
	}
	return (0);
}
