/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:12:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/01/14 14:39:09 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# define BUFF_SIZE 20

typedef struct	s_pile
{
	int			nb;
	struct s_pile	*next;
}				t_pile;

typedef struct	s_oper_fcts
{
	char		operation;
	void		(*f)(char*, t_pile**, t_pile**);
}				t_oper_fcts;

t_pile          *ft_lstnew(int nb);
void            ft_lstadd(t_pile **alst, t_pile *new);
void            ft_lstaddend(t_pile **lst, t_pile *new);
size_t          ft_lstlen(t_pile *lst);
void            ft_putlst(t_pile *lst);
void			ft_swap(int *a, int *b);

void			swap(char *operation, t_pile **a_pile, t_pile **b_pile);
void			push(char *operation, t_pile **a_pile, t_pile **b_pile);
void			rotate(char *operation, t_pile **a_pile, t_pile **b_pile);
t_oper_fcts		*make_struct(void);
int				visualizer(t_pile *a_pile, t_pile *b_pile);

#endif
