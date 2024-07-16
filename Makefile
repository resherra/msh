# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: recherra <recherra@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 06:54:06 by recherra          #+#    #+#              #
#    Updated: 2024/07/13 06:54:08 by recherra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Wextra -Werror
SRC=init.c
OBJS=$(SRC:.c=.o)
NAME=minishell
LIBFT=./libft/libft.a

all: init.h $(OBJS)
	cc $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)
clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all