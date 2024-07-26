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


const char *format_state(int type);
const char *format_type(int type);

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
		op = check_operator(str, i);
		while (str[i] && !op)
		{
			i++;
			op = check_operator(str, i);
			len++;
		}
		if (len > 0)
		{
			t_token *word = lst_new(ft_substr(str, tmp, len), WORD, GENERAL);
			lst_add_back(head, word);
		}
		if (str[i])
		{
			if (op == RED_APP || op == HERE_DOC)
			{
				t_token *double_op = lst_new(double_to_str(str, i), op, GENERAL);
				lst_add_back(head, double_op);
				i++;
			}
			else if (op == ENV)
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
				t_token *env = lst_new(ft_substr(str, tmp, len + 1), ENV, GENERAL);
				lst_add_back(head, env);
			}
			else
			{
				t_token *single_op = lst_new(char_to_str(str[i]), op, GENERAL);
				lst_add_back(head, single_op);
			}
		}
		i++;
	}
}

void set_state(t_token *head)
{
	t_token *curr;
	curr = head;

	while (curr)
	{
		if (curr->prev ==)
		curr = curr->next;
	}
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;

	//deleted the list functions by accident lol
	//	t_env *env = NULL;
	//	init_env(&env, envp);
	//deleted the list functions by accident lol
	t_token *head = NULL;
	while (1)
	{
		char *str = readline("ms-0.1$ ");
		//parse
		tokenize(str, &head);
		set_state(head);
		// traverse tokens list
		t_token *curr = head;
		while (curr)
		{
			printf("content: | '%20s' | type: | %8s | state: | %8s |\n", curr->str,  format_type(curr->type), format_state(curr->state));
			curr = curr->next;
		}

		head = NULL;
		//exec
		add_history(str);
		free(str);
	}
}



const char *format_type(int type)
{
	switch (type) {
		case D_QUOTE:
			return "D_QUOTE";
		case S_QUOTE:
			return "S_QUOTE";
		case SPACE:
			return "SPACE";
		case ENV:
			return "ENV";
		case PIPE:
			return "PIPE";
		case RED_IN:
			return "RED_IN";
		case RED_OUT:
			return "RED_OUT";
		case RED_APP:
			return "RED_APP";
		case HERE_DOC:
			return "HERE_DOC";
		default:
			return "WORD"; // Default case
	}
}

const char *format_state(int type)
{
	switch (type) {
		case IN_DOUBLE_Q:
			return "IN_DOUBLE_Q";
		case IN_QUOTE:
			return "IN_QUOTE";
		default:
			return "GENERAL"; // Default case
	}
}


