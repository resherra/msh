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

#CFLAGS=-Wall -Wextra
CFLAGS=-Wall -Wextra -fsanitize=address -g
SRC=builtins/unset.c builtins/export.c builtins/env.c init.c miscs.c lexer/env_utils.c lexer/list_utils.c  lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/lexer.c parser/parser.c
OBJS=$(SRC:.c=.o)
NAME=ms
LIBFT=libft/libft.a

all: $(NAME)

$(NAME):  init.h $(LIBFT)  $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -lreadline $(LIBFT)
	cp ${NAME} /home/resherra/.nvm/versions/node/v22.2.0/bin

$(LIBFT):
	@make -C libft/

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -rf /home/resherra/.nvm/versions/node/v22.2.0/bin/ms
	rm -rf $(NAME)

re: fclean all
