# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/08 11:49:18 by jcamhi            #+#    #+#              #
#    Updated: 2016/02/01 15:48:35 by jcamhi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
		   parsing.c \
		   linked_list.c \
		   ft_print.c \
		   find_max.c \
		   sort.c

OBJ_PATH = ./obj/

INC_PATH = ./includes

NAME = ft_ls

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -Llib/ -lft -lftprintf

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LFLAGS) $(INC) -o $@ $^ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
#	make -C libsrcs/libft
#	make -C libsrcs/ft_printf
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
#	make -C libsrcs/libft clean
#	make -C libsrcs/ft_printf clean
	/bin/rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	
fclean: clean
	rm -fv $(NAME)
#	make -C libsrcs/libft fclean
#	make -C libsrcs/ft_printf fclean

re: fclean all

.PHONY : all clean fclean re
