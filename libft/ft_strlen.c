/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:25:26 by ccepre            #+#    #+#             */
/*   Updated: 2018/12/14 14:49:58 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	size_t i;

	if (!(str))
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}