#include "init.h"

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
		case IN_S_QUOTE:
			return "IN_S_QUOTE";
		default:
			return "GENERAL"; // Default case
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
