/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:05:27 by recherra          #+#    #+#             */
/*   Updated: 2024/08/21 13:05:33 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

int	parser(t_cmd **cmd, t_token **pre, char **paths, t_env *envs)
{
	t_token	*curr;
	t_red	*new_red;
	t_cmd	*new_cmd;
	t_args	*arg;
	int		tmp;

	curr = NULL;
	new_red = NULL;
	new_cmd = NULL;
	arg = NULL;
	tmp = 0;
	curr = *pre;
	while (curr)
	{
		new_cmd = lst_new_cmd();
		while (curr && curr->type != PIPE)
		{
			while (curr && curr->type == WORD)
			{
				arg = new_arg(ft_strdup(curr->str));
				arg_add_back(&new_cmd->args_list, arg);
				new_cmd->args_lst_size++;
				curr = curr->next;
			}
			if (curr && curr->type == PIPE)
				break ;
			if (curr && curr->next && curr->next->type == WORD)
			{
				new_red = lst_new_red(curr->type, ft_strdup(curr->next->str));
				if (!ft_strlen(new_red->red_file)
					|| check_ambg(new_red->red_file, envs))
				{
					printf("msh: ambiguous redirect\n");
					new_red->is_ambegious = true;
					return (2);
				}
				red_add_back(&new_cmd->redirections, new_red);
				curr = curr->next;
			}
			else if (curr && curr->next && curr->next->type != WORD)
			{
				printf("msh: syntax error near unexpected token `%s'\n",
						curr->next->str);
				//                return (1);
			}
			else if (curr && !curr->next)
				new_cmd->unclosed = true;
			if (curr)
				curr = curr->next;
		}
		tmp = 0;
		if (new_cmd->args_list && check_in_env(new_cmd->args_list->str, envs))
			tmp = treat_env(&new_cmd->args_list);
		new_cmd->args = lst_to_arr(new_cmd->args_lst_size + tmp,
									new_cmd->args_list);
		new_cmd->cmd = new_cmd->args[0];
		new_cmd->path = extract_path(new_cmd->cmd, paths);
		cmd_add_back(cmd, new_cmd);
		if (curr)
			curr = curr->next;
	}
	return (0);
}
