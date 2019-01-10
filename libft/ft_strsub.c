/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:02:33 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/10 16:48:42 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!(s))
		return (NULL);
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	str[len] = 0;
	i = 0;
	while (len > 0)
	{
		str[i] = s[start + i];
		i++;
		len--;
	}
	return (str);
}
