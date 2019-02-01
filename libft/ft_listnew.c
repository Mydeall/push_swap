/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:07:00 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/01 14:18:47 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_listnew(void const *content, size_t content_size)
{
	t_list	*new;
	void	*cpy_content;

	if (!(new = (t_list*)malloc(sizeof(t_list) * 1)))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
		new->next = NULL;
		return (new);
	}
	if (!(cpy_content = ft_memalloc(content_size)))
		return (NULL);
	ft_memcpy(cpy_content, (void*)content, content_size);
	new->content = cpy_content;
	new->content_size = content_size;
	new->next = NULL;
	return (new);
}
