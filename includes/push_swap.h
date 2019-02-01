/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccepre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 12:12:43 by ccepre            #+#    #+#             */
/*   Updated: 2019/02/01 13:38:34 by ccepre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# define BUFF_SIZE 20
# define SUBLST_SIZE 17

typedef struct	s_pile
{
	int			nb;
	int			p;
	int			first;
	struct s_pile	*next;
}				t_pile;

typedef struct	s_oper_fcts
{
	char		action;
	void		(*f)(char*, t_pile**, t_pile**);
}				t_oper_fcts;

typedef struct	s_rules
{
	char		*action;
	int			(*f)(char*, char*);
}				t_rules;

typedef struct	s_stacks
{
	t_pile		*a_pile;
	t_pile		*b_pile;
	t_oper_fcts *fcts_tab;
	int			rr[2];
	int			rrr[2];
	t_rules		*rules_fcts;
	t_list		*pool;
}				t_stacks;

t_pile          *ft_lstnew(int nb);
void            ft_lstadd(t_pile **alst, t_pile *new);
void            ft_lstaddend(t_pile **lst, t_pile *new);
size_t          ft_lstlen(t_pile *lst);
void            ft_putlst(t_pile *lst);
void			ft_swap(int *a, int *b);
t_pile			*ft_lstgetlast(t_pile *lst);
int				ft_lstgetpos(t_pile *lst, int nb);
void			ft_freelst(t_pile *lst);
t_pile			*ft_lstcpy(t_pile *lst, int start, int end);
void			 ft_delnode(t_pile **lst, int value);

t_pile			*ft_sort(t_pile *lst);
t_pile			*make_pile(int ac, char *av[], int visualize);
void			swap(char *operation, t_pile **a_pile, t_pile **b_pile);
void			push(char *operation, t_pile **a_pile, t_pile **b_pile);
void			rotate(char *operation, t_pile **a_pile, t_pile **b_pile);
t_oper_fcts		*make_struct(void);
int				visualizer(t_pile *a_pile, t_pile *b_pile);
int				ft_quick_sort(t_stacks *stacks, char **operations,\
		t_pile **sorted);
int				append_actions(char *actions, t_stacks *stacks,\
		char **operations);
int				action_applier(char *action, t_stacks *stacks,\
		int visualize);
char			*ft_simplifier(char **operations);
int				little_list_sort(t_stacks *stacks, char **operations,\
		int index);
int				ft_lst_opposites(t_pile *pile, int *min, int *max);
int				sort_sub_lst(t_stacks *stacks, char **operations,\
		t_pile *sorted, int index);
int				push_nbr(t_stacks *stacks, char **operations, int index, int nbr);
char			*put_nbr_top(t_pile *pile, int index, int pos, t_stacks *stacks);
t_pile			*pivot_choice(t_pile *pile, t_pile *sorted);
char			*set_action(t_stacks *stacks, t_pile *pivot, t_pile *first, int index);
int				r_rules(char *pool, char *action);
int				rr_rules(char *pool, char *action);
int				s_rules(char *pool, char *action);
int				p_rules(char *pool, char *action);
t_rules			*make_rules_struct(void);

#endif
