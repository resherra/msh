/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:59:18 by recherra          #+#    #+#             */
/*   Updated: 2024/07/13 06:59:20 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	get_full_var(char *str, t_tokenizer_vars *vars)
{
	vars->env_utils.len = 0;
	vars->env_utils.tmp = vars->i;
	vars->i++;
	while (str[vars->i] && !check_operator(str, vars->i))
	{
		vars->env_utils.len++;
		vars->i++;
	}
	vars->i--;
}

int	handle_env(char *str, t_tokenizer_vars *vars, t_token **head)
{
	t_token	*last_node;

	get_full_var(str, vars);
	last_node = get_last_node(head);
	while (last_node && last_node->type != HERE_DOC)
		last_node = last_node->prev;
	if (last_node)
	{
		if (check(str, vars->tmp))
		{
			vars->i++;
			return (1);
		}
		vars->content = lst_new(ft_substr(str, vars->env_utils.tmp,
					vars->env_utils.len + 1), WORD, GENERAL);
	}
	else
		vars->content = lst_new(ft_substr(str, vars->env_utils.tmp,
					vars->env_utils.len + 1), ENV, GENERAL);
	return (0);
}

void	handle_simple_word(char *str, t_tokenizer_vars *vars, t_token **head)
{
	vars->len = 0;
	vars->tmp = vars->i;
	vars->op = check_operator(str, vars->i);
	while (str[vars->i] && !vars->op)
	{
		vars->i++;
		vars->op = check_operator(str, vars->i);
		vars->len++;
	}
	if (vars->len > 0)
	{
		vars->content = lst_new(ft_substr(str, vars->tmp, vars->len), WORD,
				GENERAL);
		lst_add_back(head, vars->content);
	}
}

void	skip_spaces(char *str, t_tokenizer_vars *vars)
{
	while (str[vars->i] == ' ') //work on the other spaces later;
		vars->i++;
}

void	handle_double_operators(char *str, t_tokenizer_vars *vars)
{
	vars->content = lst_new(double_to_str(str, vars->i), vars->op, GENERAL);
	vars->i++;
}

void	tokenize(char *str, t_token **head)
{
	t_tokenizer_vars	vars;

	vars.i = 0;
	skip_spaces(str, &vars);
	while (str[vars.i])
	{
		handle_simple_word(str, &vars, head);
		if (str[vars.i])
		{
			if (vars.op == RED_APP || vars.op == HERE_DOC)
				handle_double_operators(str, &vars);
			else if (vars.op == ENV)
			{
				if (handle_env(str, &vars, head))
					continue ;
			}
			else
				vars.content = lst_new(char_to_str(str[vars.i]), vars.op,
						GENERAL);
			lst_add_back(head, vars.content);
		}
		vars.i++;
	}
}

void	lexer(char *str, t_token **head, t_env *env, t_token **pre)
{
	tokenize(str, head);
	if (set_state(*head, env))
	{
		printf("syntax error\n");
		exit(1);
	}
	sanitize(*head, pre);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_token	*head;
	t_token	*pre;
	char	*str;

	(void)ac;
	(void)av;
	(void)envp;
	env = NULL;
	init_env(&env, envp);
	head = NULL;
	pre = NULL;
	//env list
	//	traverse_env_list(env);
	while (1)
	{
		str = readline("ms-0.1$ ");
		lexer(str, &head, env, &pre);
		//traverse primary tokens list;
		traverse_primary_tokens_list(head);
		printf("\n\n");
		//traverse pre-parse list;
		traverse_primary_tokens_list(pre);
		//		clear the list
		lstclear(&head, freed);
		lstclear(&pre, freed);
		head = NULL;
		pre = NULL;
		system("leaks -q ms");
		add_history(str);
		free(str);
	}
}
