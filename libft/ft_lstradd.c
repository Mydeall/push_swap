/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstradd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 19:19:39 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/01 14:21:54 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listradd(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!(lst))
		return ;
	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = NULL;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
	current->next->next = NULL;
}
