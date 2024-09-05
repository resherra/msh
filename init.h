/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 07:00:03 by recherra          #+#    #+#             */
/*   Updated: 2024/09/05 18:27:58 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

typedef struct s_cmd	t_cmd;

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

//macros for errors
# define not_valid_idntf -2
# define allocation_error -3

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
}						t_type;

//state
typedef enum e_state
{
	IN_DOUBLE_Q,
	IN_S_QUOTE,
	GENERAL
}						t_state;

//token's element
typedef struct s_token
{
	char				*str;
	t_type				type;
	t_state				state;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

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
t_token					*lst_new(char *str, t_type type, t_state state);
void					lst_add_back(t_token **head, t_token *node);


//env
typedef struct s_env
{
	char				*key;
	char				*value;
	bool				in_export;
	struct s_env		*next;
}						t_env;

void					tokenize(char *str, t_token **head);

void					skip_spaces(char *str, t_tokenizer_vars *vars);

int						lexer(char *str, t_token **head, t_env *env,
							t_token **pre);

//state function
int						set_state(t_token *head, t_env *env);

//variables expansion
void					expansion(t_token *var, t_env *envs,
							bool in_double_quotes);

//tokens content utils
char					*char_to_str(char c);
char					*double_to_str(char *str, int i);

//env utils
//void				extract_env(t_env **envs, char *str, char ***paths);
void					init_env(t_env **env, char **envp, char ***paths);
void					ft_env_addback(t_env **env, t_env *new);

//pre-parse functions
void					sanitize(t_token *head, t_token **new);

//env list utils
t_env					*new_env(char *key, char *value);
void					env_addback(t_env **env, t_env *new);
void					ft_env_addback(t_env **env, t_env *new);

void					env_delone(t_env *env, void (*del)(void *));

//tokenizer miscs
t_token					*get_last_node(t_token **head);

//operator checks & others
int						check_operator(char *str, int i);
int						check(char *str, int tmp);



int	join_check(t_token *token);
int	handle_single_dollar(t_token **curr);


void					lstclear(t_token **head);

//Built-ins
int						unset(t_env **envs, char **vars);
int						env(t_env *envs);
int						ft_export(t_env *envs, char **args);
int						ft_echo(char **str);
int						ft_cd(char *path);
int						pwd(void);
void					ft_exit(t_cmd **cmd);

//PARSINGd
typedef struct s_red
{
	t_type				red_type;
	char				*red_file;
	bool				is_ambegious;
	bool                expanded;
	struct s_red		*next;
}						t_red;

typedef struct s_args
{
	char				*str;
	struct s_args		*next;
}						t_args;

typedef struct s_cmd
{
	char				*cmd;
	char				*path;
	t_args				*args_list;
	int					args_lst_size;
	char				**args;
	t_red				*redirections;
	bool				unclosed;
	struct s_cmd		*next;
}						t_cmd;

int						parser(t_cmd **cmd, t_token **pre, char **paths,
							t_env *envs);

t_cmd					*lst_new_cmd(void);
void					cmd_add_back(t_cmd **cmd, t_cmd *new);

t_args					*new_arg(char *str);
void					arg_add_front(t_args **lst, t_args *new);
void					arg_add_back(t_args **args, t_args *new);

t_red					*lst_new_red(t_type red_type, char *red_file, bool expanded);
void					red_add_back(t_red **redirections, t_red *new);

char					**lst_to_arr(int size, t_args *args_list);
char					*extract_path(char *cmd, char **paths);
int						check_in_env(char *str, t_env *envs);
int						check_ambg(char *str, t_env *envs);
int						treat_env(t_args **args_list);

typedef struct s_data
{
	t_env				*envs;
	t_token				*head;
	t_token				*pre;
	t_cmd				*cmd;
	char				**paths;
	char				*str;
}						t_data;

// excution
typedef struct execution_tools
{
	char *red_out;
	char *herdc_content;
	int number_of_herd;
	char *red_input;
	int fd_out;
	int prev;
	int fd_inp;
	char *error;
	int fd[2];
}t_red_info;

void					excution(t_env **env, t_cmd *cmd, char **envp,
							int *pid);
int						implement_redirections(t_red *redr, t_red_info *red_infom , int *pid);
int						is_bultin(t_env **envs, t_cmd *cmd);
int						sample_bultin(t_env **envs, t_cmd *cmd);

void					free_cmd_list(t_cmd **cmds);

t_env					*new_env_export(char *key, char *value);

//miscs
const char				*format_state(int type);
const char				*format_type(int type);
void					traverse_primary_tokens_list(t_token *env);
void					traverse_env_list(t_env *env);
int						test_builtins(char *str, t_env **envs, t_cmd *cmd);
void					freed(void *str);
void					traverse_parse_list(t_cmd *cmd);

#endif
