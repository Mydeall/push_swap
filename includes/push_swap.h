/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:12:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/10 17:18:33 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# define BUFF_SIZE 20

typedef struct	s_oper_fcts
{
	char		operation;
	void		(*f)(char*, int**, int**, int(*)[2]);
}				t_oper_fcts;

void			ft_swap(int *a, int *b);
void			ft_strdel(char **as);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_strsplit(char const *s, char c);
long long int	ft_atoi(const char *str);
size_t			ft_strlen(const char *str);
char			*ft_strchr(const char *s, int c);

void			swap(char *operation, int **a_pile, int **b_pile, int (*size)[2]);
void			push(char *operation, int **a_pile, int **b_pile, int (*size)[2]);
void			rotate(char *operation, int **a_pile, int **b_pile, int (*size)[2]);
t_oper_fcts		*make_struct(void);

#endif
