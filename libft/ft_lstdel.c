/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 16:24:10 by ccepre            #+#    #+#             */
/*   Updated: 2019/03/01 14:13:05 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_listdel(t_list **alst)
{
	t_list	*lst;
	t_list	*lstn;

	if (!(alst))
		return ;
	lst = *alst;
	while (lst != NULL)
	{
		lstn = lst->next;
		free((lst)->content);
		free(lst);
		lst = lstn;
	}
	free(lst);
	free(lstn);
	*alst = NULL;
}
