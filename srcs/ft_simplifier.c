/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simplifier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:49:59 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/28 14:50:19 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft.h"

static int	compute_len(char **tab)
{
	int i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}
static char	**rm_strtab(char **tab, int start, int end)
{
	int i;
	int j;
	int len;
	char **new_tab;

	len = compute_len(tab);
//	printf("lem : %d | start %d | end %d\n", len, start, end);
	if (!(new_tab = (char**)malloc(sizeof(char*) * (len - (end - start)))))
		return (NULL);
	new_tab[len - (end - start) - 1] = 0;
//	printf("end - start : %d\n", len - (end - start) - 1);
	i = -1;
	j = -1;
	while (++i <= len)
	{
		j++;
		if (i == start)
			i += end - start + 1;
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
	int		len;

//	ft_putstrtab(operations);
	if (!operations || !*operations)
		return (NULL);
	i = -1;
	len = compute_len(operations);
	while (++i < len)
	{
//		printf("i : %d\n", i);
//		printf("test i + 1 : %d\n", ft_strcmp(operations[i + 1], "test"));
		if ((!(ft_strcmp(operations[i], "pb")) && !(ft_strcmp(operations[i + 1],"pa"))) ||\
				(!(ft_strcmp(operations[i], "pa")) && !(ft_strcmp(operations[i + 1], "pb"))))
		{
			j = 1;
			while (i >= j && ((!(ft_strcmp(operations[i - j], "pb")) && !(ft_strcmp(operations[i + 1 + j],"pa"))) ||\
				(!(ft_strcmp(operations[i - j], "pa")) && !(ft_strcmp(operations[i + 1 + j], "pb")))))
				j++;
			tmp = operations;
			operations = rm_strtab(operations, i - j + 1, i + j);
//			ft_putstrtab(operations);
			free(tmp);
			len = compute_len(operations);
		}
	}
	result = ft_strjointab((const char **)operations, "\n");
	while (*operations)
	{
		free(*operations);
		operations++;
	}
	return (result);
}
