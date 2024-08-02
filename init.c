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

int	check_operator(char *str, int i)
{
	if (*(str + i) == ' ')
		return (SPACE);
	else if (*(str + i) == '|')
		return (PIPE);
	else if (*(str + i) == '$')
		return (ENV);
	else if (*(str + i) == '\'')
		return (S_QUOTE);
	else if (*(str + i) == '\"')
		return (D_QUOTE);
	else if (*(str + i) == '>')
	{
		if (!ft_strncmp(">>", str + i, 2))
			return (RED_APP);
		return (RED_OUT);
	}
	else if (*(str + i) == '<')
	{
		if (!ft_strncmp("<<", str + i, 2))
			return (HERE_DOC);
		return (RED_IN);
	}
	return (WORD);
}

t_token	*get_last_node(t_token **head)
{
	t_token	*curr;

	curr = *head;
	while (curr && curr->next)
		curr = curr->next;
	return (curr);
}

void	join(t_token **curr, char **str)
{
	char *tmp;
	while ((*curr) && (*curr)->type != SPACE)
	{
		if (ft_strlen((*curr)->str) == 1)
		{
			if (((*curr)->type == ENV && (*curr)->state == GENERAL)
				&& (*curr)->next && ((*curr)->next->type == D_QUOTE
					|| (*curr)->next->type == S_QUOTE))
			{
				*curr = (*curr)->next;
				continue ;
			}
		}
		if ((*curr)->type == D_QUOTE || (*curr)->type == S_QUOTE)
		{
			*curr = (*curr)->next;
			continue ;
		}
		tmp = *str;
		*str = ft_strjoin(*str, (*curr)->str);
		free(tmp);
		*curr = (*curr)->next;
	}
}

void	sanitize(t_token *head, t_token **new)
{
	t_token	*curr;
	t_token	*node;
	char	*str;

	curr = head;
	while (curr)
	{
		str = NULL;
		join(&curr, &str);
		if (str)
		{
			node = lst_new(str, WORD, GENERAL);
			lst_add_back(new, node);
		}
		if (curr)
			curr = curr->next;
	}
}

typedef struct s_env_token_utils
{
	int	len;
	int	tmp;
}		t_env_token_utils;

int	check(char *str, int tmp)
{
	if (check_operator(str, tmp) == ENV && (check_operator(str, tmp
				+ 1) == D_QUOTE || check_operator(str, tmp + 1) == S_QUOTE))
	{
		return (1);
	}
	return (0);
}

void	tokenize(char *str, t_token **head)
{
	int					i;
	int					len;
	int					tmp;
	int					op;
	t_token				*content;
	t_env_token_utils	env_utils;
	t_token				*last_node;

	i = 0;
	while (str[i] == ' ') //work on the other spaces later;
		i++;
	while (str[i])
	{
		len = 0;
		tmp = i;
		op = check_operator(str, i);
		while (str[i] && !op)
		{
			i++;
			op = check_operator(str, i);
			len++;
		}
		if (len > 0)
		{
			content = lst_new(ft_substr(str, tmp, len), WORD, GENERAL);
			lst_add_back(head, content);
		}
		if (str[i])
		{
			if (op == RED_APP || op == HERE_DOC)
			{
				content = lst_new(double_to_str(str, i), op, GENERAL);
				i++;
			}
			else if (op == ENV)
			{
				env_utils.len = 0;
				env_utils.tmp = i;
				i++;
				while (str[i] && !check_operator(str, i))
				{
					env_utils.len++;
					i++;
				}
				i--;
				last_node = get_last_node(head);
				while (last_node && last_node->type != HERE_DOC)
					last_node = last_node->prev;
				if (last_node)
				{
					if (check(str, tmp))
					{
						i++;
						continue ;
					}
					content = lst_new(ft_substr(str, env_utils.tmp,
								env_utils.len + 1), WORD, GENERAL);
				}
				else
					content = lst_new(ft_substr(str, env_utils.tmp,
								env_utils.len + 1), ENV, GENERAL);
			}
			else
				content = lst_new(char_to_str(str[i]), op, GENERAL);
			lst_add_back(head, content);
		}
		i++;
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


void	lstclear(t_token **lst, void (*del)(void *));
void    freed(void *str);

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


void    freed(void *str)
{
	free(str);
}

void	lstclear(t_token **token, void (*del)(void *))
{
	t_token	*ne;

	if (!token || !del)
		return ;
	if (*token)
	{
		while (*token)
		{
			ne = *token;
			*token = (*token)->next;
			del(ne->str);
			free(ne);
		}
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
