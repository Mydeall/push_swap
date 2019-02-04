/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pool_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:50:34 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/04 19:47:40 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

t_pool	*ft_poolgetpos(t_pool *pool, int pos)
{
	t_pool	*current;

	current = pool;
	while (pos-- && current)
		current = current->next;
	return (current);
}

void	ft_putpool(t_pool *lst)
{
	ft_putstr("{\n");
	if (!(lst))
		ft_putstr("(null)\n");
	while (lst)
	{
		ft_putchar('|');
		ft_putstr(lst->action);
		ft_putchar('|');
		ft_putchar('\n');
		lst = lst->next;
	}
	ft_putstr("}\n");
}

void	ft_pooladd(t_pool **alst, t_pool *new)
{
	t_pool	*lst;

	if (alst)
	{
		lst = *alst;
		new->next = lst;
		*alst = new;
	}
}

t_pool	*ft_poolnew(char *action)
{
	t_pool	*new;

	if (!(new = (t_pool*)malloc(sizeof(t_pool) * 1)))
		return (NULL);
	new->action = ft_strdup(action);
	new->next = NULL;
	return (new);
}

void	ft_pooldel_node(t_pool **pool, int pos)
{
	t_pool	*prev;
	t_pool	*current;
	int		i;

	current = *pool;
	prev = NULL;
	i = -1;
	while (++i < pos)
	{
		prev = current;
		current = current->next;
	}
	if (prev)
		prev->next = current->next;
	else
		*pool = current->next;
	free(current->action);
	free(current);
}

char	*ft_pooljoin(t_pool *pool)
{
	t_pool	*current;
	int		size;
	char	*result;

	current = pool;
	size = 0;
	while (current)
	{
		size += ft_strlen(current->action) + 1;
		current = current->next;
	}
	if (!(result = (char*)ft_memalloc(size)))
		return (NULL);
	current = pool;
	size = 0;
	while (current)
	{
		ft_strcat(result, current->action);
		if (current->next)
			ft_strcat(result, "\n");
		current = current->next;
	}
	return (result);
}
