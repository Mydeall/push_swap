/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_visualizer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 11:56:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/16 14:27:57 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	find_max(t_pile *a_pile, t_pile *b_pile)
{
	t_pile *current;
	int		int_max;

	current = a_pile;
	int_max = 0;
	while (current)
	{
		if (current->nb > int_max)
			int_max = current->nb;
		current = current->next;
	}
	current = b_pile;
	while (current)
	{
		if (current->nb > int_max)
			int_max = current->nb;
		current = current->next;
	}
	return (int_max);
}

static int	determine_value(int len, int len_o, t_pile **pile,\
		int *value)
{
	*value = 0;
	if (len >= len_o)
	{
		*value = (*pile)->nb;
		*pile = (*pile)->next;
		return (len - 1);
	}
	return (len);
}

static int	display_values(int a_value, int b_value, int int_max)
{
	char	*a_str;
	char	*b_str;

	if (!(a_str= (char*)malloc(a_value + 1)) ||\
				!(b_str= (char*)malloc(b_value + 1)))
		return (1);
	a_str= ft_memset(a_str, '|', a_value);
	b_str= ft_memset(b_str, '|', b_value);
	a_str[a_value] = 0;
	b_str[b_value] = 0;
	printf("%*s  %*s\n", int_max, a_str, int_max, b_str);
	free(a_str);
	free(b_str);
	return (0);
}

int			visualizer(t_pile *a_pile, t_pile *b_pile)
{
	int		int_max;
	int		len[2];
	int		a_value;
	int		b_value;
	int		tmp;

	int_max = find_max(a_pile, b_pile);
	len[0] = ft_lstlen(a_pile);
	len[1] = ft_lstlen(b_pile);
//	sleep(1);
	system("clear");
	while (len[0] || len[1])
	{
		tmp = determine_value(len[0], len[1], &a_pile, &a_value);
		len[1] = determine_value(len[1], len[0], &b_pile, &b_value);
		len[0] = tmp;
		if (display_values(a_value, b_value, int_max))
			return (1);
	}
	return (0);
}
