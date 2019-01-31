# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccepre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/01/30 15:36:44 by ccepre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_CHECK = checker

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft
SRC_PATH = ./srcs
INC_PATH = ./includes
MAIN_PATH = ./..

LIB_NAME = ft_strcpy.c\
		   ft_strdel.c\
		   ft_atoi.c\
		   ft_strdup.c\
		   ft_strsub.c\
		   ft_strcat.c\
		   ft_strchr.c\
		   ft_strjoin.c\
		   ft_strjoinarg.c\
		   ft_strnew.c\
		   ft_strcmp.c\
		   ft_strlen.c\
		   ft_bzero.c\
		   ft_memalloc.c\
		   ft_memset.c\
		   ft_itoa_base.c\
		   ft_pow.c \
		   ft_strsplit.c \
		   ft_swap.c \
		   ft_isdigit.c \
		   ft_putstrtab.c \
		   ft_putstr.c \
		   ft_putchar.c \
		   ft_putendl.c \
		   ft_putinttab.c \
		   ft_putnbr.c \
		   ft_itoa.c \
		   ft_strjointab.c \
		   ft_abs.c \
		   ft_strstr.c

SRC_NAME_CHECK= ft_checker.c \
				ft_oper_fcts.c \
				ft_visualizer.c \
				lst_fcts.c \
				ft_make_pile.c \
				ft_operations_applier.c

SRC_NAME_PUSH = ft_push_swap.c \
				ft_oper_fcts.c \
				ft_visualizer.c \
				ft_quick_sort.c \
				lst_fcts.c \
				ft_make_pile.c \
				ft_operations_applier.c \
				ft_simplifier.c \
				ft_sublst_sort.c \
				ft_selection_sort.c \
				ft_normal_sorting.c

INC_NAME = push_swap.h \
		   libft.h

SRC_PUSH = $(addprefix $(SRC_PATH)/, $(SRC_NAME_PUSH))
SRC_CHECK = $(addprefix $(SRC_PATH)/, $(SRC_NAME_CHECK))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

OBJ_SRC_PUSH= $(SRC_PUSH:.c=.o)
OBJ_SRC_CHECK= $(SRC_CHECK:.c=.o)
OBJ_LIB= $(LIB:.c=.o)

all : $(NAME)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@ -I $(INC_PATH) 

.PHONY : clean fclean re

$(NAME) : $(OBJ_SRC_PUSH) $(OBJ_SRC_CHECK) $(OBJ_LIB) $(INC)
	gcc -o $(NAME) $(OBJ_SRC_PUSH) $(OBJ_LIB) -I $(INC_PATH)
	gcc -o $(NAME_CHECK) $(OBJ_SRC_CHECK) $(OBJ_LIB) -I $(INC_PATH)

clean :
	rm -f $(OBJ_SRC_PUSH)
	rm -f $(OBJ_SRC_CHECK)
	rm -f $(OBJ_LIB)

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_CHECK)

re : fclean all

san : $(OBJ_SRC_PUSH) $(OBJ_SRC_CHECK) $(OBJ_LIB) $(INC)
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC_PUSH) $(OBJ_LIB) -I $(INC_PATH)
	gcc -g3 -fsanitize=address -o $(NAME_CHECK) $(OBJ_SRC_CHECK) $(OBJ_LIB) -I $(INC_PATH)
