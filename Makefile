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

CFLAGS=-Wall -Wextra -fsanitize=address -g
SRC=init.c env_utils.c list_utils.c
OBJS=$(SRC:.c=.o)
NAME=ms
LIBFT=./libft/libft.a

all: init.h $(OBJS)
	cc $(CFLAGS) -lreadline $(LIBFT) $(OBJS) -o $(NAME)
	cp ${NAME} /Users/recherra/Library/Python/3.9/bin

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all