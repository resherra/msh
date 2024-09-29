/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakkou <schakkou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:35:22 by recherra          #+#    #+#             */
/*   Updated: 2024/09/29 21:49:11 by schakkou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static void	get_full_var(char *str, t_tokenizer_vars *vars)
{
	vars->env_utils.len = 0;
	vars->env_utils.tmp = vars->i;
	vars->i++;
	if (str[vars->i] && !ft_isalpha(*(str + vars->i)) && *(str + vars->i) != '_'
		&& *(str + vars->i) != '"' && *(str + vars->i) != '\'')
	{
		vars->env_utils.len++;
		return ;
	}
	if (str[vars->i] && str[vars->i] == '?')
	{
		vars->env_utils.len++;
		return ;
	}
	while (str[vars->i] && !check_operator(str, vars->i) && (ft_isalnum(*(str
					+ vars->i)) || *(str + vars->i) == '_'))
	{
		vars->env_utils.len++;
		vars->i++;
	}
	vars->i--;
}

static int	handle_env(char *str, t_tokenizer_vars *vars, t_token **head)
{
	t_token	*last_node;

	get_full_var(str, vars);
	last_node = get_last_node(head);
	while (last_node && sm_check(last_node->type))
		last_node = last_node->prev;
	if (last_node && last_node->type == HERE_DOC)
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

static void	handle_simple_word(char *str, t_tokenizer_vars *vars,
		t_token **head)
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

static void	handle_double_operators(char *str, t_tokenizer_vars *vars)
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
			vars.i++;
		}
	}
}
