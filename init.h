/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 07:00:03 by recherra          #+#    #+#             */
/*   Updated: 2024/07/13 07:00:04 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "libft/libft.h"
# include <curses.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <dirent.h> //closedir, readdir, opendir
# include <fcntl.h>  //open
# include <readline/history.h>
# include <readline/readline.h> //readline, rl_clear_history, rl_on_new_line,
//rl_replace_line, rl_redisplay, add_history
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset,
//									kill
# include <stdio.h>     //printf, perror, strerror
# include <stdlib.h>    //malloc, free, exit, getenv
# include <sys/ioctl.h> //ioctl
# include <sys/stat.h>  //stat, lstat
# include <sys/wait.h>  //wait, waitpid, wait3, wait4
# include <termios.h>   //tcgetattr, tcsetattr
# include <unistd.h>    //write, close, fork, pipe, dup, dup2, ttyslot,
//										ttyname,
//	ttyslot, isatty, chdir, unlink, execve, read, getcwd

//tokens
typedef enum e_type
{
	WORD,
	D_QUOTE,
	S_QUOTE,
	SPACE,
	ENV,
	PIPE,
	RED_IN,
	RED_OUT,
	RED_APP,
	HERE_DOC,
}					t_type;

//state
typedef enum e_state
{
	IN_DOUBLE_Q,
	IN_S_QUOTE,
	GENERAL
}					t_state;

//token's element
typedef struct s_token
{
	char			*str;
	t_type			type;
	t_state			state;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

//tokenizer vars
typedef struct s_env_token_utils
{
	int					len;
	int					tmp;
}						t_env_token_utils;

typedef struct s_tokenizer_vars
{
	int					i;
	int					len;
	int					tmp;
	int					op;
	t_token				*content;
	t_env_token_utils	env_utils;
}						t_tokenizer_vars;




//d-list functions
t_token				*lst_new(char *str, t_type type, t_state state);
void				lst_add_back(t_token **head, t_token *node);




//env
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void	tokenize(char *str, t_token **head);

void	skip_spaces(char *str, t_tokenizer_vars *vars);

void	lexer(char *str, t_token **head, t_env *env, t_token **pre);


//state function
int					set_state(t_token *head, t_env *env);

//variables expansion
void				expansion(t_token *var, t_env *envs);

//tokens content utils
char				*char_to_str(char c);
char				*double_to_str(char *str, int i);

//env utils
void				extract_env(t_env **envs, char *str);
void				init_env(t_env **env, char **envp);

//pre-parse functions
void	sanitize(t_token *head, t_token **new);

//env list utils
t_env				*new_env(char *key, char *value);
void				env_addback(t_env **env, t_env *new);

//tokenizer miscs
t_token	*get_last_node(t_token **head);

//operator checks & others
int	check_operator(char *str, int i);
int	check(char *str, int tmp);


//tree
typedef struct s_tree
{
	char			*place_holder;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;


//env
void				init_env(t_env **env, char **envp);

//miscs
const char			*format_state(int type);
const char			*format_type(int type);
void				traverse_primary_tokens_list(t_token *env);
void				traverse_env_list(t_env *env);
void	lstclear(t_token **token, void (*del)(void *));
void    freed(void *str);

#endif
