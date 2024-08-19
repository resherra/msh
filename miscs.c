/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/08/19 00:51:28 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "./init.h"

const char	*format_type(int type)
{
	switch (type)
	{
	case D_QUOTE:
		return ("D_QUOTE");
	case S_QUOTE:
		return ("S_QUOTE");
	case SPACES:
		return ("SPACES");
	case ENV:
		return ("ENV");
	case PIPE:
		return ("PIPE");
	case RED_IN:
		return ("RED_IN");
	case RED_OUT:
		return ("RED_OUT");
	case RED_APP:
		return ("RED_APP");
	case HERE_DOC:
		return ("HERE_DOC");
	default:
		return ("WORD"); // Default case
	}
}

const char	*format_state(int type)
{
	switch (type)
	{
	case IN_DOUBLE_Q:
		return ("IN_DOUBLE_Q");
	case IN_S_QUOTE:
		return ("IN_S_QUOTE");
	default:
		return ("GENERAL"); // Default case
	}
}

void	lstclear(t_token **head)
{
	t_token	*ne;

	if (!head)
		return ;
	if (*head)
	{
		while (*head)
		{
			ne = *head;
			*head = (*head)->next;
			free(ne->str);
			free(ne);
		}
	}
	*head = NULL;
}

void	traverse_primary_tokens_list(t_token *token)
{
	t_token	*curr;

	curr = token;
	while (curr)
	{
		printf("content: | '%s' | type: | %8s | state: | %8s |\n", curr->str,
				format_type(curr->type), format_state(curr->state));
		curr = curr->next;
	}
}

void	traverse_env_list(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		printf("key: %s | value: %s\n", curr->key, curr->value);
//        printf("%s=%s\n", curr->key, curr->value);
        curr = curr->next;
	}
}


void	traverse_parse_list(t_cmd *cmd)
{
	t_cmd *curr = NULL;

	curr = cmd;
	while (curr)
	{
		printf("\n\n\nUnclosed heredoc: %d\n\nPipes: %d\n\ncommand: %s\n\npath: %s\n\narg list size: %d\n\n", cmd->unclosed, cmd->pipes, curr->cmd, curr->path, curr->args_lst_size);
		printf("arguments: ");
		int i = 0;
		while (curr->args[i])
		{
			printf(" %s |", curr->args[i++]);
		}
		printf("\n\n");
		printf("redirections:\n");
		t_red *tmp = curr->redirections;
		while (tmp)
		{
			printf("\tredirection file: %s\n\tredirection type: %s\n", tmp->red_file, format_type(tmp->red_type));
			tmp = tmp->next;
		}

		curr = curr->next;
	}
}



// int test_builtins(char *str, t_env **envs, t_cmd *cmd)
// {

// 	write(1, "12\n", 3);
// 	if (cmd && cmd->cmd && !strcmp("exit", cmd->cmd))
// 		exit(1);
// 	else if (!cmd->next && !strcmp("cd", cmd->cmd))
// 	{
// 		// write(1, cmd->args[1], 2);
// 		// write(1, "1\n", 2);
// 		ft_cd(cmd->args[1]);
// 		cmd = cmd->next;
// 		//return ( 1);
// 	}
// 	excution(envs, cmd);
	
//     return 0;
// }