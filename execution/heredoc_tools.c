/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/28 21:41:58 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static char	*ft_join(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(len + 2, sizeof(char));
	if (!res)
		return (NULL);
	while (s1 && s1[j])
	{
		res[j] = s1[j];
		j++;
	}
	while (s2 && s2[i])
	{
		res[j + i] = s2[i];
		i++;
	}
	res[j + i] = '\n';
	return (res);
}

static char	*extract_value(char *value, int start, int end, char *str)
{
	char	*res;
	char	*var;

	str[start - 1] = 0;
	res = ft_strjoin(str, value);
	var = res;
	if (res && str[end])
	{
		res = ft_strjoin(res, str + end);
		free(var);
		if (!res)
			return (NULL);
	}
	return (free(str), res);
}

static char	*is_exist(t_env *env, char *str, int start, int *new)
{
	char	*var;
	int		end;

	var = ft_substr(str, start, (*new - start));
	if (!var)
		return (NULL);
	end = *new;
	while (env)
	{
		if (!ft_strcmp(var, env->key))
		{
			printf("start == %i, new == %i\n", start, end);
			*new = start + ft_strlen(env->value) - 2;
			printf("start == %i\n", *new);
			free(var);
			return (extract_value(env->value, start, end, str));
		}
		env = env->next;
	}
	*new = start - 1;
	while (str[end])
	{
		str[start - 1] = str[end++];
		start++;
	}
	str[start - 1] = 0;
	return (str);
}

static char	*expand(char *str, t_env *env, int i, int *new_index)
{
	char	*tmp;
	int		j;

	printf("now == %i, i == %i\n", *new_index, i);
	tmp = str;
	if (!tmp[i++])
		return (str);
	*new_index = i;
	j = i;
	if (tmp[j] == '_' || ft_isalpha(tmp[j]))
		j++;
	else if (ft_isdigit(tmp[j]))
	{
		printf("1 inp == %s\n", str);
		while (str[j])
		{
			str[i - 1] = str[++j];
			i++;
		}
		str[i] = 0;
		printf(" inp == %s\n", str);
		return (str);
	}
	else
		return (str);
	printf("now2.0 == %i\n", *new_index);
	while (ft_isalnum(tmp[j]) || tmp[j] == '_')
		j++;
	printf("now2 == %i\n", *new_index);
	*new_index = j;
	return (is_exist(env, str, i, new_index));
}

void	save_herdoc_data(t_env *env, t_red *hrdc, char *input,
		t_red_info *red_info)
{
	char	*tmp;
	int		i;
	int		new_index;

	i = 0;
	if (hrdc->expanded)
	{
		while (input[i])
		{
			if (input[i] == '$')
			{
				input = expand(input, env, i, &new_index);
				printf("s == %i\n", new_index);
				printf("\n\n\n\n");
				i = new_index - 1;
			}
			i++;
		}
		if (!input)
			return (perror("msh-0.1$ "), free(input),
				free(red_info->herdc_content), exit(1));
	}
	tmp = red_info->herdc_content;
	red_info->herdc_content = ft_join(red_info->herdc_content, input);
	if (!red_info->herdc_content)
		return (perror("msh-0.1$ "), free(tmp), free(input), exit(1));
	free(tmp);
}
