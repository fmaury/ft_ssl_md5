# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/04 11:00:31 by fmaury            #+#    #+#              #
#    Updated: 2019/09/05 11:20:42 by fmaury           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COMPILER		= gcc

CC_FLAGS		= -Wall -Werror -Wextra

NAME			= ft_ssl

INC			= ./inc/

LIB_INC			= ./libft/srclib

SRC_DIR		= ./srcs

OBJS_DIR		= ./.objs

SRC			= 	main.c \
				parse_arg.c \
				dispatch.c \
				md5.c \
				sha256.c \
				handle_algo.c \
				render.c \
				err.c

OBJ			= $(SRC:.c=.o)

SRCS			= $(addprefix $(SRC_DIR)/, $(SRC))

OBJS			= $(addprefix $(OBJS_DIR)/, $(OBJ))

all : $(NAME) $(OTOOL_NAME)

$(NAME): $(OBJS) $(INC)
	MAKE -C libft/
	$(COMPILER) $(CC_FLAGS) -I $(LIB_INC) $(OBJS) -o $(NAME) -L ./libft -lft

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c $(INC)/ssl.h
	mkdir -p $(OBJS_DIR)
	$(COMPILER) $(CC_FLAGS) -I $(INC) -I $(LIB_INC) -c $< -o $@

clean:
	MAKE clean -C libft/
	rm -rf $(OBJ)

fclean: clean
	MAKE fclean -C libft/
	rm -rf $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re
