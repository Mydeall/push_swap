/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pile_memory_fcts.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:26:24 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:26:12 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

t_pile	*ft_nodecpy(t_pile *lst)
{
	t_pile	*cpy;

	if (!(cpy = ft_lstnew(lst->nb)))
		return (NULL);
	cpy->p = lst->p;
	cpy->first = lst->first;
	return (cpy);
}

t_pile	*ft_lstcpy(t_pile *lst, int end)
{
	t_pile	*current;
	t_pile	*cpy;
	t_pile	*start_cpy;
	int		i;

	current = lst;
	cpy = NULL;
	i = -1;
	while (++i <= end && current)
	{
		if (!cpy)
		{
			if (!(cpy = ft_nodecpy(current)))
				return (NULL);
			start_cpy = cpy;
		}
		else
		{
			if (!(cpy->next = ft_nodecpy(current)))
				return (NULL);
			cpy = cpy->next;
		}
		current = current->next;
	}
	return (start_cpy);
}

void	ft_freelst(t_pile *lst)
{
	t_pile	*tmp;

	printf("%p\n", lst);
	while (lst)
	{
		printf("ok\n");
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
	printf("%p\n", lst);
}

void	ft_delnode(t_pile **lst, int value)
{
	t_pile *prev;
	t_pile *current;

	current = *lst;
	prev = NULL;
	while (current)
	{
		if (current->nb == value)
		{
			if (prev)
				prev->next = current->next;
			else
				*lst = current->next;
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_freepool(t_pool *lst)
{
	t_pool	*tmp;

	while (lst)
	{
		tmp = lst;
		free(lst->action);
		lst = lst->next;
		free(tmp);
	}
}
