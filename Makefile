# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apple <apple@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 06:54:06 by recherra          #+#    #+#              #
#    Updated: 2024/08/19 18:02:32 by apple            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Wextra
# CFLAGS=-Wall -Wextra -fsanitize=address -g
SRC=execution/is_bult_in.c execution/execution_tools.c execution/execution.c builtins/exit.c builtins/env_tools.c builtins/pwd.c builtins/cd.c builtins/echo.c builtins/unset.c builtins/export.c builtins/env.c init.c miscs.c lexer/init_env.c lexer/env_utils.c lexer/list_utils.c  lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/lexer.c parser/parser.c parser/arg_list_utils.c parser/cmd_list_utils.c parser/red_list_utils.c
OBJS=$(SRC:.c=.o)
NAME=ms
LIBFT=libft/libft.a

all: $(NAME)

$(NAME):  init.h $(LIBFT)  $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -lreadline $(LIBFT)
	cp ms /Users/recherra/Library/Python/3.9/bin

$(LIBFT):
	@make -C libft/

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all
