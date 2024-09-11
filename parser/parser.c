/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:05:27 by recherra          #+#    #+#             */
/*   Updated: 2024/09/05 18:12:16 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

void	fill_cmd(t_cmd **cmd, t_cmd *new_cmd, t_env *envs, char **paths)
{
	int	tmp;

	tmp = 0;
	if (new_cmd->args_list && check_in_env(new_cmd->args_list->str, envs))
		tmp = treat_env(&new_cmd->args_list);
	new_cmd->args = lst_to_arr(new_cmd->args_lst_size + tmp,
								new_cmd->args_list);
	new_cmd->cmd = new_cmd->args[0];
	new_cmd->path = extract_path(new_cmd->cmd, paths);
	cmd_add_back(cmd, new_cmd);
}

t_token	*get_args(t_token *curr, t_args *arg, t_cmd *new_cmd)
{
	while (curr && curr->type == WORD)
	{
		arg = new_arg(ft_strdup(curr->str));
		arg_add_back(&new_cmd->args_list, arg);
		new_cmd->args_lst_size++;
		curr = curr->next;
	}
	return (curr);
}

t_token	*get_redirections(t_token *curr, t_red *new_red, t_cmd *new_cmd,
		t_env *envs)
{
	if (curr->next->state == IN_DOUBLE_Q)
		new_red = lst_new_red(curr->type, ft_strdup(curr->next->str), false);
	else
		new_red = lst_new_red(curr->type, ft_strdup(curr->next->str), true);
	if (!ft_strlen(new_red->red_file) || check_ambg(new_red->red_file, envs))
		new_red->is_ambegious = true;
	red_add_back(&new_cmd->redirections, new_red);
	curr = curr->next;
	return (curr);
}

t_token	*heredoc_special_handling(t_token *curr, t_red *new_red, t_cmd *new_cmd,
		t_env *envs)
{
	if (curr && curr->next && curr->next->type == WORD)
        curr = get_redirections(curr, new_red, new_cmd, envs);
	else if (curr && curr->next && curr->next->type != WORD)
		new_cmd->unclosed = true;
	else if (curr && !curr->next)
        new_cmd->unclosed = true;
	return (curr);
}

int	parser(t_cmd **cmd, t_token **pre, char **paths, t_env *envs)
{
	t_token	*curr;
	t_red	*new_red;
	t_cmd	*new_cmd;
	t_args	*arg;

	arg = NULL;
	new_red = NULL;
	curr = *pre;
	while (curr)
	{
		new_cmd = lst_new_cmd();
		while (curr && curr->type != PIPE)
		{
			curr = get_args(curr, arg, new_cmd);
			if (curr && curr->type == PIPE)
				break ;
			curr = heredoc_special_handling(curr, new_red, new_cmd, envs);
			if (curr)
				curr = curr->next;
		}
		fill_cmd(cmd, new_cmd, envs, paths);
		if (curr)
			curr = curr->next;
	}
	return (0);
}
