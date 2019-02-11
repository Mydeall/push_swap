/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pool_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 14:50:34 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/11 18:07:49 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_pool	*ft_poolgetpos(t_pool *pool, int pos)
{
	t_pool	*current;

	current = pool;
	while (pos-- && current)
		current = current->next;
	return (current);
}

int		ft_pooladd(t_pool **alst, t_pool *new)
{
	t_pool	*lst;

	if (!new || !alst)
		return (1);
	lst = *alst;
	new->next = lst;
	if (lst)
		lst->prev = new;
	new->prev = NULL;
	*alst = new;
	return (0);
}

t_pool	*ft_poolnew(char *action)
{
	t_pool	*new;

	if (!(new = (t_pool*)malloc(sizeof(t_pool) * 1)))
		return (NULL);
	new->action = ft_strdup(action);
	new->next = NULL;
	new->prev = NULL;
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
	if (current->next)
		current->next->prev = prev;
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
	if (!pool)
		return (ft_strdup(""));
	while (current->next)
	{
		size += ft_strlen(current->action) + 1;
		current = current->next;
	}
	size += ft_strlen(current->action) + 1;
	if (!(result = (char*)ft_memalloc(size + 1)))
		return (NULL);
	size = 0;
	while (current)
	{
		ft_strcat(result, current->action);
		if (current->prev)
			ft_strcat(result, "\n");
		current = current->prev;
	}
	return (result);
}
