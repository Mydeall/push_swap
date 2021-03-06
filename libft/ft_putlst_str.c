/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlst_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:12:09 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/25 11:32:31 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlst_str(t_list *lst)
{
	t_list *current;

	ft_putstr("{\n");
	if (!(lst))
		ft_putstr("(null)\n");
	current = lst;
	while (current)
	{
		ft_putchar('|');
		ft_putstr(current->content);
		ft_putchar('|');
		ft_putchar('\n');
		current = current->next;
	}
	ft_putstr("}\n");
}
