# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/08 11:49:18 by jcamhi            #+#    #+#              #
#    Updated: 2015/12/11 16:36:47 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c \
		get_next_line.c

OBJ_PATH = ./obj/

INC_PATH = ./includes

NAME = ft_ls

CC = gcc

CFLAGS = -Werror -Wextra -Wall -g

LFLAGS = -Llib/ -lft 

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(LFLAGS) $(INC) -o $@ $^ 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
#	make -C libft
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $< 

clean:
#	make -C libft clean
	/bin/rm -fv $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	
fclean: clean
	rm -fv $(NAME)
#	@make -C libft fclean
#	@make -C minilibx fclean

re: fclean all

.PHONY : all clean fclean re
