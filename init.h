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



//to be deleted;
#include "string.h"


typedef struct s_cmd t_cmd;

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
	SPACES,
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
	bool            in_export;
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
void				extract_env(t_env **envs, char *str, char ***paths);
void				init_env(t_env **env, char **envp, char ***paths);

//pre-parse functions
void	sanitize(t_token *head, t_token **new);

//env list utils
t_env				*new_env(char *key, char *value);
void				env_addback(t_env **env, t_env *new);
void	env_delone(t_env *env, void (*del)(void *));

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

//miscs
const char			*format_state(int type);
const char			*format_type(int type);
void				traverse_primary_tokens_list(t_token *env);
void				traverse_env_list(t_env *env);
void	lstclear(t_token **token, void (*del)(void *));
int test_builtins(char *str, t_env **envs, t_cmd *cmd);
void    freed(void *str);

//Built-ins
void    unset(t_env *envs, char **vars);
void    env(t_env *envs);
void    export(t_env **envs, t_cmd *cmd);


//PARSING
typedef struct s_red
{
	t_type red_type;
	char *red_file;
	struct s_red *next;
} t_red;

typedef struct s_args
{
	char *str;
	struct s_args *next;
} t_args;

typedef struct s_cmd
{
	char *cmd; //command
	char *path; //command path
	t_args *args_list; //arguments in a list (command uncluded) to be converted to 2d arr
	int	args_lst_size; //argument list size
	char **args; //2d arr of args
	t_red	*redirections; //redirections list
	struct s_cmd *next;
} t_cmd;

void    parser(t_cmd **cmd, t_token *pre, char **paths);

t_cmd *lst_new_cmd();
void    cmd_add_back(t_cmd **cmd, t_cmd *new);

t_args *new_arg(char *str);
void arg_add_back(t_args **args, t_args *new);

t_red *lst_new_red(t_type red_type, char *red_file);
void    red_add_back(t_red **redirections, t_red *new);



//miscs
void	traverse_parse_list(t_cmd *cmd);
//PARSING

#endif
