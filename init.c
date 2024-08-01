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

int check_operator(char *str, int i)
{
	if (*(str + i) == ' ')
		return SPACE;
	else if (*(str + i) == '|')
		return PIPE;
	else if (*(str + i) == '$')
		return ENV;
	else if (*(str + i) == '\'')
		return S_QUOTE;
	else if (*(str + i) == '\"')
		return D_QUOTE;
	else if (*(str + i) == '>')
	{
		if (!ft_strncmp(">>", str + i, 2))
			return RED_APP;
		return RED_OUT;
	}
	else if (*(str + i) == '<')
	{
		if (!ft_strncmp("<<", str + i, 2))
			return HERE_DOC;
		return RED_IN;
	}
	return WORD;
}

char *char_to_str(char c)
{
	char *new = malloc(sizeof(char) * 2);
	if (!new)
		return NULL;
	new[0] = c;
	new[1] = 0;
	return new;
}

char *double_to_str(char *str, int i)
{
	char *new = malloc(sizeof(char) * 3);
	if (!new)
		return NULL;
	new[0] = *(str + i);
	new[1] = *(str + i + 1);
	new[2] = 0;
	return new;
}


t_token *get_last_node(t_token **head)
{
	t_token *curr;

	curr = *head;
	while (curr && curr->next)
			curr = curr->next;
	return curr;
}

void    tokenize(char *str, t_token **head)
{
	int i;
	int len;
	int tmp;
	int op;

	i = 0;
	while (str[i] == ' ') //work on the other spaces later;
		i++;
	while (str[i])
	{
		len = 0;
		tmp = i;
		//save the operator found;
		op = check_operator(str, i);
		//while its work, traverse the string
		while (str[i] && !op)
		{
			i++;
			op = check_operator(str, i);
			len++;
		}
		//get the whole word;
		if (len > 0)
		{
			t_token *word = lst_new(ft_substr(str, tmp, len), WORD, GENERAL);
			lst_add_back(head, word);
		}
		//if there's no operator, we'll not enter here!
		if (str[i])
		{
			if (op == RED_APP || op == HERE_DOC)
			{
				t_token *double_op = lst_new(double_to_str(str, i), op, GENERAL);
				lst_add_back(head, double_op);
				i++;
			} else if (op == ENV)
			{
				int len = 0;
				int tmp = i;
				i++;
				while (str[i] && !check_operator(str, i))
				{
					len++;
					i++;
				}
				i--;

				t_token *last_node = get_last_node(head);
				while (last_node && (last_node->type == SPACE || last_node->type == D_QUOTE))
					last_node = last_node->prev;
				if (last_node && last_node->type == HERE_DOC)
				{
					t_token *non_expanded_env = lst_new(ft_substr(str, tmp, len + 1), WORD, GENERAL);
					lst_add_back(head, non_expanded_env);
				} else
				{
					t_token *env = lst_new(ft_substr(str, tmp, len + 1), ENV, GENERAL);
					lst_add_back(head, env);
				}


			} else
			{
				t_token *single_op = lst_new(char_to_str(str[i]), op, GENERAL);
				lst_add_back(head, single_op);
			}
		}
		i++;
	}
}

void    expansion(t_token *var, t_env *envs)
{
	t_env *curr = envs;
	int len = ft_strlen(var->str);

	if (len == 1)
	{
		var->str = ft_strdup("$");
		var->type = WORD;
		return;
	}
	while (curr)
	{
		if (!ft_strncmp(var->str + 1, curr->key, len - 1))
		{
			var->str = curr->value;
			var->type = WORD;
			return;
		}
		curr = curr->next;
	}
	var->str = ft_strdup("");
	var->type = WORD;
}

void set_state(t_token *head, t_env *env)
{
	t_token *curr;
	bool doub_quote_flag = false;
	bool sing_quote_flag = false;
	curr = head;
	while (curr)
	{
		//double quote check
		if (curr->type == D_QUOTE)
		{
			doub_quote_flag = true;
			curr = curr->next;
			while (curr && curr->type != D_QUOTE)
			{
				if (curr->type == ENV)
					expansion(curr, env);
				else
					curr->type = WORD;
				curr->state = IN_DOUBLE_Q;
				curr = curr->next;
			}
			if (curr)
				doub_quote_flag = false;
		}

		//single quote check
		if (curr && curr->type == S_QUOTE)
		{
			sing_quote_flag = true;
			curr = curr->next;
			while (curr && curr->type != S_QUOTE)
			{
//				if (curr->type == ENV)
//					curr->type = WORD;
				curr->type = WORD;
				curr->state = IN_S_QUOTE;
				curr = curr->next;
			}
			if (curr)
				sing_quote_flag = false;
		}

		if (curr && curr->type == ENV)
			expansion(curr, env);

		if (doub_quote_flag  == true || sing_quote_flag == true)
		{
			printf("Syntax Error\n");
			exit(1);
		}
		if (curr)
			curr = curr->next;
	}
}

//today


int check_token(t_token *token)
{
	if (token->type == WORD)
		return 1;
	if (token->type == D_QUOTE || token->type == S_QUOTE)
		return 2;
	return 0;
}

//		while its not a space with state general and its not an operator -> join and p
//      skip the spaces
//      skip the operators with state GENERAL

void    sanitize(t_token *head, t_token **new)
{
	t_token *curr = head;

	while (curr)
	{
		char *str = NULL;
		while (curr && curr->type != SPACE)
		{
			if (curr->type == D_QUOTE || curr->type == S_QUOTE)
			{
				curr = curr->next;
				continue;
			}
			str = ft_strjoin(str, curr->str);
			curr = curr->next;
		}
		if (str)
		{
			t_token *node = lst_new(str, WORD, GENERAL);
			lst_add_back(new, node);
		}
		if (curr)
			curr = curr->next;
	}
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	t_env *env = NULL;
	init_env(&env, envp);
	t_token *head = NULL;
	t_token *pre = NULL;

	//env list
	//	traverse_env_list(env);
	while (1)
	{
		char *str = readline("ms-0.1$ ");
		tokenize(str, &head);
		set_state(head, env);
		sanitize(head, &pre);

		//traverse primary tokens list;
		traverse_primary_tokens_list(head);
		printf("\n\n");
		traverse_primary_tokens_list(pre);
		pre = NULL;
		head = NULL;
		add_history(str);
		free(str);
	}
}


//miscs
void    traverse_primary_tokens_list(t_token *token)
{
	t_token *curr = token;

	while (curr)
	{
		printf("content: | '%s' | type: | %8s | state: | %8s |\n", curr->str,  format_type(curr->type), format_state(curr->state));
		curr = curr->next;
	}
}

void    traverse_env_list(t_env *env)
{
	t_env *curr = env;

	while (curr)
	{
		printf("key: %s | value: %s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
