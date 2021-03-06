/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fcts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:10:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/25 12:21:48 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pile	*ft_lstnew(int nb)
{
	t_pile	*new;

	if (!(new = (t_pile*)malloc(sizeof(t_pile) * 1)))
		return (NULL);
	new->nb = nb;
	new->p = 0;
	new->first = 0;
	new->next = NULL;
	return (new);
}

void	ft_lstadd(t_pile **alst, t_pile *new)
{
	t_pile	*lst;

	if (alst)
	{
		lst = *alst;
		new->next = lst;
		*alst = new;
	}
}

void	ft_lstaddend(t_pile **lst, t_pile *new)
{
	t_pile *current;

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

size_t	ft_lstlen(t_pile *lst)
{
	size_t	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

int		ft_lstgetpos(t_pile *lst, int nb)
{
	t_pile	*current;
	int		i;

	current = lst;
	i = -1;
	while (current)
	{
		i++;
		if (current->nb == nb)
			break ;
		if (!current->next && current->nb != nb)
			return (-1);
		current = current->next;
	}
	return (i);
}
