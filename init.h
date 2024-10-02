/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/29 21:48:24 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "libft/libft.h"
# include "string.h"
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

int						g_pid;

# define NOT_VALID_IDNTF -2
# define ALLOCATION_ERROR -3

typedef struct s_cmd	t_cmd;

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

typedef enum e_state
{
	IN_DOUBLE_Q,
	IN_S_QUOTE,
	GENERAL
}						t_state;

typedef struct s_token
{
	char				*str;
	t_type				type;
	t_state				state;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

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

t_token					*lst_new(char *str, t_type type, t_state state);
void					lst_add_back(t_token **head, t_token *node);

typedef struct s_env
{
	char				*key;
	char				*value;
	bool				in_export;
	struct s_env		*next;
}						t_env;

typedef struct s_red
{
	t_type				red_type;
	char				*red_file;
	bool				is_ambegious;
	bool				expanded;
	struct s_red		*next;
}						t_red;

typedef struct s_args
{
	char				*str;
	struct s_args		*next;
}						t_args;

typedef struct s_dl
{
	char				*dilemeter;
	int					expand;
	struct s_dl			*next;
}						t_delmtr;

typedef struct s_parser_vars
{
	t_token				*curr;
	t_red				*new_red;
	t_cmd				*new_cmd;
	t_args				*arg;
	int					counter;
}						t_parser_vars;

typedef struct s_cmd
{
	char				*cmd;
	char				*path;
	t_args				*args_list;
	int					args_lst_size;
	int					nmbr_of_herdc;
	int					is_herdc;
	char				**args;
	t_red				*redirections;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	t_env				*envs;
	t_token				*head;
	t_token				*pre;
	t_cmd				*cmd;
	char				*str;
	char				**envp;
}						t_data;

typedef struct s_util_vars
{
	char				*trimmed_value;
	char				*full_key;
}						t_util_vars;

typedef struct s_flags
{
	bool				flag;
	bool				expanded_empty;
	bool				quotes_stick;
}						t_flags;

void					lstclear(t_token **head);
void					clear_args_list(t_args **head);
void					clear_redirections(t_red **head);
void					free_all(t_cmd *cmd);
void					free_cmd_list(t_cmd **cmds);

void					init_all(t_data *data);
void					clear_all(t_data *data);

char					**lst_to_envp(t_env *envs);

void					tokenize(char *str, t_token **head);

void					skip_spaces(char *str, t_tokenizer_vars *vars);

int						set_state(t_token *head, t_env *env);

void					expansion(t_token *var, t_env *envs,
							bool in_double_quotes);

char					*char_to_str(char c);
char					*double_to_str(char *str, int i);

void					init_env(t_env **env, char **envp);
void					ft_env_addback(t_env **env, t_env *new);

void					sanitize(t_token *head, t_token **new);

t_env					*new_env(char *key, char *value);
void					env_addback(t_env **env, t_env *new);
void					ft_env_addback(t_env **env, t_env *new);

void					env_delone(t_env *env, void (*del)(void *));

t_token					*get_last_node(t_token **head);

int						check_operator(char *str, int i);
int						check(char *str, int tmp);
int						sm_check(int type);

int						join_check(t_token *token);
int						handle_single_dollar(t_token **curr);

void					lstclear(t_token **head);

int						unset(t_env **envs, char **vars);
int						env(t_env *envs, t_cmd *cmd);
int						ft_export(t_env *envs, char **args);
int						ft_echo(char **str);
int						ft_cd(char *path, t_env *env);
int						pwd(void);
int						ft_exit(t_cmd *cmd, char *exit_state);


void					parser(t_cmd **cmd, t_token **pre, t_env *envs);
t_cmd					*lst_new_cmd(void);
void					cmd_add_back(t_cmd **cmd, t_cmd *new);

t_args					*new_arg(char *str);
void					arg_add_front(t_args **lst, t_args *new);
void					arg_add_back(t_args **args, t_args *new);

t_red					*lst_new_red(t_type red_type, char *red_file,
							bool expanded);
void					red_add_back(t_red **redirections, t_red *new);

char					**lst_to_arr(int size, t_args *args_list);
char					*extract_path(char *cmd, t_env *envs);
int						check_in_env(char *str, t_env *envs);
int						check_ambg(char *str, t_env *envs);
int						treat_env(t_args **args_list);

char					*free_and_return(char *pre_path, char *to_return,
							char **paths);

void					special_case(t_token *curr, t_token **new,
							t_token **node);

int						lexer(char *str, t_token **head, t_env *env,
							t_token **pre);

void					count_heredoc(t_parser_vars *vars);
void					init_vars(t_parser_vars *vars, t_token **pre);

typedef struct execution_tools
{
	char				*red_out;
	char				*herdc_content;
	char				*red_input;
	int					is_one_cmd;
	int					number_of_herd;
	int					nmbr_cmd_herdc;
	int					fd_out;
	int					check;
	int					prev;
	int					fd_inp;
	int					fd[2];
	int					pfds[2];
}						t_red_info;

void					sig_handle(int sig);
void					excution(t_env **env, t_cmd *cmd, int *pid);

int						implement_redirections(t_red *redr,
							t_red_info *red_infom,
							t_env *env,
							int herdc_child);
int						is_bultin(t_env **envs, t_cmd *cmd, int is_one_cmd);
int						sample_bultin(t_env **envs, t_cmd *cmd,
							t_red_info *red_info);
void					free_cmd_list(t_cmd **cmds);
void					save_herdoc_data(t_env *env, t_red *hrdc, char *input,
							t_red_info *red_info);
char					**pre_excution(t_env **env, t_cmd *cmd,
							t_red_info *red_info, char **envp);

char					**lst_to_envp(t_env *envs);
void					free_envp(char **envp);
void					error(int err, char *path);
void					exit_state(t_env **env, int state, int smpl_state,
							char **envp);

int						print_syntax_error(char *str);
int						all_space_var(char *str);
char					*ultimate_trim(char *str);
char					**get_paths(char *value);
void					free_paths(char **paths);
t_token					*create_node(char *str, t_flags flags);
int						expanded_empty_check(t_token *curr, t_flags *flags);
int						sticked_quotes_check(t_token *curr);

int						get_act_paths(char **paths, char **path,
							char **pre_path);
void					free_paths(char **paths);
char					**get_new_paths(t_env *envs);
int						pth(char *paths, char **path, char **pre_path);

const char				*format_state(int type);
const char				*format_type(int type);
void					traverse_primary_tokens_list(t_token *env);
void					traverse_env_list(t_env *env);
int						test_builtins(char *str, t_env **envs, t_cmd *cmd);
void					freed(void *str);
void					traverse_parse_list(t_cmd *cmd);


#endif
