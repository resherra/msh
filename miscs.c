/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miscs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/09/04 19:38:12 by apple            ###   ########.fr       */
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
        curr = curr->next;
	}
}

void	traverse_parse_list(t_cmd *cmd)
{
	t_cmd *curr = NULL;

	curr = cmd;
	while (curr)
	{
		printf("\n\n\ncommand: %s\n\npath: %s\n\narg list size: %d\n\n", curr->cmd, curr->path, curr->args_lst_size);
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
            if (tmp->red_type == HERE_DOC)
            {
                if (tmp->expanded)
                    printf("\texpanded: %s\n", "true");
                else
                    printf("\texpanded: %s\n", "false");
            }
			tmp = tmp->next;
		}

		curr = curr->next;
	}
}

//to be deleted
void	traverse(t_token *head, t_token *pre, t_cmd *cmd)
{
    (void)head;
    (void)pre;
    (void)cmd;
    //traverse_primary_tokens_list(head);
    // traverse_primary_tokens_list(pre);
    //clear the list
//     printf("\n\n\n");
//     traverse_parse_list(cmd);
//     printf("\n\n\n");
}