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

CFLAGS=-Wall -Wextra
SRC=init.c miscs.c lexer/env_utils.c lexer/list_utils.c  lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/lexer.c
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