/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:49:59 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/17 19:54:38 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static char	**rm_strtab(char **tab, int start, int end)
{
	int i;
	int j;
	int len;
	char **new_tab;

	len = 0;
	while (tab && tab[len])
		len++;
	printf("len = %d | start : %d | end : %d\n", len, start, end);
	if (!(new_tab = (char**)malloc(sizeof(char*) * (len - (end - start) + 1))))
		return (NULL);
	printf("size malloc : %d\n", (len - (end - start) + 1));
	new_tab[len - end - start] = 0;
	i = -1;
	j = -1;
	while (tab[++i])
	{
		j++;
		if (i == start)
			i += end - start;
		new_tab[j] = tab[i];
	}
	return (new_tab);
}

char		*ft_simplifier(char **operations)
{
	int		i;
	int		j;
	char	**tmp;
	char	*result;

	if (!operations || !*operations)
		return (NULL);
	i = -1;
	printf("start\n");
	while (operations[++i])
	{
		printf("action : %s\n", operations[i]);
		if ((!(ft_strcmp(operations[i], "pb")) && !(ft_strcmp(operations[i + 1],"pa"))) ||\
				(!(ft_strcmp(operations[i], "pa")) && !(ft_strcmp(operations[i + 1], "pb"))))
		{
			j = i + 2;
			while ((!(ft_strcmp(operations[++i], "pb")) && !(ft_strcmp(operations[j],"pa"))) ||\
				(!(ft_strcmp(operations[i], "pa")) && !(ft_strcmp(operations[j], "pb"))))
				j++;
			tmp = operations;
			operations = rm_strtab(operations, i - 1, j - 1);
			ft_putstrtab(operations);
			free(tmp);
		}
	}
	result = ft_strjointab((const char **)operations, "\n");
	while (*operations)
	{
		free(*operations);
		operations++;
	}
	free(operations);
	return (result);
}
