/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fcts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 14:10:27 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/30 17:40:55 by ccepre           ###   ########.fr       */
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

int	ft_lstgetpos(t_pile *lst, int nb)
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

void	ft_putlst(t_pile *lst)
{
	ft_putstr("{\n");
	if (!(lst))
		ft_putstr("(null)\n");
	while (lst)
	{
		ft_putchar('|');
		ft_putnbr(lst->nb);
		ft_putstr(" : ");
		ft_putnbr(lst->p);
		ft_putchar('|');
		ft_putchar('\n');
		lst = lst->next;
	}
	ft_putstr("}\n");
}

t_pile	*ft_lstgetlast(t_pile *lst)
{
	t_pile	*current;

	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

t_pile	*ft_nodecpy(t_pile *lst)
{
	t_pile	*cpy;

	if (!(cpy = ft_lstnew(lst->nb)))
		return (NULL);
	cpy->p = lst->p;
	cpy->first = lst->first;
	return (cpy);
}

t_pile	*ft_lstcpy(t_pile *lst, int start, int end)
{
	t_pile	*current;
	t_pile	*cpy;
	t_pile	*start_cpy;
	int i;

	current = lst;
	cpy = NULL;
	i = -1;
	while (++i <= end && current)
	{
		if (i >= start)
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
		}
		current = current->next;
	}
	return (start_cpy);
}

void	ft_freelst(t_pile *lst)
{
	t_pile	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
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
