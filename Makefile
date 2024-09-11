# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apple <apple@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 06:54:06 by recherra          #+#    #+#              #
#    Updated: 2024/09/10 19:21:36 by apple            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Wextra
 CFLAGS=-Wall -Wextra -fsanitize=address -g -I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib
#SRC=execution/is_bult_in.c execution/execution_tools.c execution/execution.c builtins/exit.c builtins/env_tools.c builtins/pwd.c builtins/cd.c builtins/echo.c builtins/unset.c builtins/export.c builtins/env.c init.c miscs.c lexer/init_env.c lexer/env_utils.c lexer/list_utils.c  lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/lexer.c parser/parser.c parser/arg_list_utils.c parser/cmd_list_utils.c parser/red_list_utils.c
# CFLAGS=-Wall -Wextra
# CFLAGS=-Wall -Wextra -fsanitize=address -g
#CFLAGS=-Wall -Wextra -fsanitize=address -g -I/Users/recherra/goinfre/homebrew/Cellar/readline/8.2.13/include -L/Users/recherra/goinfre/homebrew/Cellar/readline/8.2.13/lib
SRC=execution/is_bult_in.c execution/execution_tools.c execution/execution.c builtins/exit.c builtins/env_tools.c builtins/pwd.c builtins/cd.c builtins/echo.c builtins/unset.c builtins/export.c builtins/env.c init.c miscs.c lexer/init_env.c lexer/env_utils.c lexer/list_utils.c  lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/sanitize_miscs.c lexer/lexer.c parser/parser.c parser/arg_list_utils.c parser/cmd_list_utils.c parser/red_list_utils.c parser/ambegious.c parser/env_exec.c parser/parser_miscs.c
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
