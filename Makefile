# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/13 06:54:06 by recherra          #+#    #+#              #
#    Updated: 2024/09/29 21:51:06 by schakkou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS=-Wall -Wextra -Werror -I/Users/$(USER)/goinfre/homebrew/Cellar/readline/8.2.13/include
SRC=init_miscs.c envp_utils.c clear.c execution/execution_of_heredoc.c execution/heredoc_tools.c execution/redirections.c  execution/execution_tools.c execution/execution.c builtins/exit.c builtins/env_tools.c builtins/pwd.c builtins/cd.c builtins/echo.c builtins/unset.c builtins/export.c builtins/env.c init.c lexer/init_env.c lexer/env_utils.c lexer/list_utils.c lexer/pre_parse_func_utils.c lexer/state.c lexer/expansion.c lexer/tokens_content_utils.c lexer/pre_parse_func.c lexer/tokenize_miscs.c lexer/check.c lexer/tokenizer_core.c lexer/sanitize_miscs.c lexer/lexer.c parser/parser.c parser/arg_list_utils.c parser/cmd_list_utils.c parser/red_list_utils.c parser/ambegious.c parser/env_exec.c parser/parser_miscs.c parser/parser_miscs_exp_utils.c parser/parser_miscs_utils.c parser/parser_miscs_exp.c
OBJS=$(SRC:.c=.o)
NAME=msh
LIBFT=libft/libft.a

all: $(NAME)

$(NAME):  init.h $(LIBFT)  $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS) -lreadline -L/Users/$(USER)/goinfre/homebrew/Cellar/readline/8.2.13/lib $(LIBFT)

$(LIBFT):
	@make -C libft/

clean:
	make -C libft/ clean
	rm -rf $(OBJS)

fclean: clean
	make -C libft/ fclean
	rm -rf $(NAME)

re: fclean all