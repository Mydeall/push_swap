# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccepre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/08 15:43:12 by ccepre            #+#    #+#              #
#    Updated: 2019/02/15 12:21:37 by ccepre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_CHECK = checker

FLAGS = -Wall -Wextra -Werror

LIB_PATH = ./libft
SRC_PATH = ./srcs
INC_PATH = ./includes

SRC_NAME_CHECK = ft_checker.c \
				ft_operations_fcts.c \
				ft_visualizer.c \
				ft_pile_basic_fcts.c \
				ft_lst_memory_fcts.c \
				ft_make_pile.c \
				ft_operations_applier.c \
				ft_action_rules.c \
				ft_action_rules_struct.c \
				ft_pool_fcts.c \
				ft_nbr_manipulation.c

SRC_NAME_PUSH = ft_push_swap.c \
				ft_operations_fcts.c \
				ft_isolate_sublst.c \
				ft_quick_sort.c \
				ft_visualizer.c \
				ft_pile_basic_fcts.c \
				ft_lst_memory_fcts.c \
				ft_pool_fcts.c \
				ft_make_pile.c \
				ft_operations_applier.c \
				ft_sublst_sort.c \
				ft_selection_sort.c \
				ft_normal_sorting.c \
				ft_action_rules.c \
				ft_action_rules_struct.c \
				ft_nbr_manipulation.c

INC_NAME = push_swap.h \
		   libft.h \
		   ft_printf.h

SRC_PUSH = $(addprefix $(SRC_PATH)/, $(SRC_NAME_PUSH))
SRC_CHECK = $(addprefix $(SRC_PATH)/, $(SRC_NAME_CHECK))
INC = $(addprefix $(INC_PATH)/, $(INC_NAME))

OBJ_SRC_PUSH= $(SRC_PUSH:.c=.o)
OBJ_SRC_CHECK= $(SRC_CHECK:.c=.o)

all : libft $(NAME)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@ -I $(INC_PATH) 

.PHONY : libft clean fclean re

$(NAME) : $(OBJ_SRC_PUSH) $(OBJ_SRC_CHECK) $(INC) $(LIB_PATH)/libft.a
	gcc -o $(NAME) $(OBJ_SRC_PUSH) $(LIB_PATH)/libft.a -I $(INC_PATH)
	gcc -o $(NAME_CHECK) $(OBJ_SRC_CHECK) $(LIB_PATH)/libft.a -I $(INC_PATH)

libft :
	@cd $(LIB_PATH) ; $(MAKE) -f Makefile

clean :
	rm -f $(OBJ_SRC_PUSH)
	rm -f $(OBJ_SRC_CHECK)
	rm -f $(OBJ_LIB)
	cd $(LIB_PATH) ; $(MAKE) fclean 

fclean : clean
	rm -f $(NAME)
	rm -f $(NAME_CHECK)

re : fclean all

san : $(OBJ_SRC_PUSH) $(OBJ_SRC_CHECK) $(OBJ_LIB) $(INC)
	cd $(LIB_PATH) ; $(MAKE) -f Makefile
	gcc -g3 -fsanitize=address -o $(NAME) $(OBJ_SRC_PUSH) $(LIB_PATH)/libft.a -I $(INC_PATH)
	gcc -g3 -fsanitize=address -o $(NAME_CHECK) $(OBJ_SRC_CHECK) $(LIB_PATH)/libft.a -I $(INC_PATH)
