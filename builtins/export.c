#include "../init.h"

int	cheek_idntf_error(char *str)
{
	int var_len;

	var_len = 0;
	if (str[var_len] != '_' && !ft_isalpha(str[var_len++]))
	{
		printf("export: `%s' : not a valid identifier\n", str);	
		return (NOT_VALID_IDNTF);
	}
	while (str[var_len] != 0 && str[var_len] != '=' && (ft_isalnum(str[var_len]) || str[var_len] == '_'))
		var_len++;
	if (str[var_len] == '=' || str[var_len] == 0)
		return (var_len);
	printf("export: `%s' : not a valid identifier\n", str);	
	return(NOT_VALID_IDNTF);
}

int	add_in_env(char *var, t_env *envs)
{
	int		len_value;
	int		Name_var_len;
	char	*var_name;
	char	*var_value;
	t_env	*new_var;

	var_value = NULL;
	Name_var_len = cheek_idntf_error(var);
	len_value = ft_strlen(var) - Name_var_len - 1;
	if (Name_var_len  == NOT_VALID_IDNTF)
		return (NOT_VALID_IDNTF);
	var_name = ft_substr(var, 0, Name_var_len);
	if (len_value >= 0)
	{
		var_value = ft_substr(var, Name_var_len + 1, len_value);
	}
	if (!var_name || (!var_value && len_value > 0))
		return(ALLOCATION_ERROR);
	new_var = new_env_export(var_name, var_value);
	ft_env_addback(&envs, new_var);
	return (1);
}

int    ft_export(t_env *envs, char **args)
{
    t_env	*curr;
	int		state;
	int		i;

    curr = envs;
	state = 0;
	i = 1;
	if (args[i])
	{
		while (args[i])
			state += add_in_env(args[i++], envs);
		if(state != (i - 1))
			return(1);
		return (0);
	}
	 curr = curr->next;
    	while (curr)
    	{
        	printf("declare -x %s", curr->key);
			if (curr->value)
				printf("=\"%s\"", curr->value);
			printf("\n");
        	curr = curr->next;
    	}
	return (0);
}
