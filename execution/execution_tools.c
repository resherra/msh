#include "../init.h"

static char	*ft_join(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	// if (!s1)
	// 	return ft_strdup(s2);
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

char *extract_value(char *value, int start, int end, char *str)
{
	char *res;
	char *var;

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
		return(free(str),res);
}
static char	*is_exist(t_env *env, char *str, int start, int end)
{
	char *var;

	var = ft_substr(str, start, (end - start));
	if (!var)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(var, env->key))
		{
			free(var);
	
			return (extract_value(env->value, start, end, str));
		}
		env = env->next;
	}
	while (str[end])
	{
		str[start - 1] = str[end++];
		start++;
	}
	str[start - 1] = 0;
	return(str);
}

void	cat_variable(int j, int i, char *str)
{
	while (str[j])
	{
		str[i - 1] = str[++j];
		i++;
	}
	str[i] = 0;
}
char	*expand(char *str, t_env *env)
{
	char *tmp;
	int j;
	int i;

	tmp = str;	
	i = 0;
	while (tmp[i] != '$' && tmp[i])
		i++;
	if (!tmp[i++])
		return (str);
	j = i;
	if (tmp[j] == '_' || ft_isalpha(tmp[j]))
		j++;
	else if (ft_isdigit(tmp[j]))
		return (cat_variable(j, i, str), str);
	else
		return(str);
	while (ft_isalnum(tmp[j]) || tmp[j] == '_')
		j++;
	tmp = is_exist(env, str, i, j);
	if (!tmp)
	{
		return(free(str), perror("msh-0.1$ "), NULL);
	}
	return(tmp);
}

void	save_herdoc_data(t_env *env, t_red *hrdc, char *input, t_red_info *red_info)
{
	char	*tmp;

	if (hrdc->expanded)
	{
		input = expand(input, env);
		if (!input)
		{
			free(red_info->herdc_content);
			exit(1);
		}
	}
	tmp = red_info->herdc_content;
	red_info->herdc_content = ft_join(red_info->herdc_content, input);
	if (!red_info->herdc_content)
	{
		free(tmp);
		free(input);
		perror("msh-0.1$ ");
		exit(1);
	}
	free(tmp);
	free(input);
}
static int heredoc(t_red *hrdc, t_red_info *red_info, t_env *env)
{
    char    *input;

	while (hrdc->red_type != HERE_DOC)
		hrdc = hrdc->next;
    while (1)
    {
        input = readline(">");
        if (!input)
			return(0);	
        if (!ft_strcmp(input , hrdc->red_file))
        {
			red_info->number_of_herd--;
            if (red_info->number_of_herd == 0)
				return (free(input), 1);
			hrdc = hrdc->next;
			while (hrdc->red_type != HERE_DOC)
				hrdc = hrdc->next;			
        }
		else if (red_info->number_of_herd == 1) 
		{
			save_herdoc_data(env, hrdc, input, red_info);
		}
    }
	return(0);
}

int red_out(t_red *redir, t_red_info *redir_info)
{
	int fd;

	fd = -1;
	if (redir->red_type == RED_OUT)
	{
		redir_info->red_out = redir->red_file;
		fd = open(redir_info->red_out, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
		if (fd < 0)
        	return (perror("msh-0.1$ "), 0);
		redir_info->fd_out = -3;
	}
	else if (redir->red_type == RED_APP)
	{
		redir_info->red_out = redir->red_file;
		 fd = open(redir->red_file, O_CREAT | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
		if (fd < 0)
       		return (perror("msh-0.1$ "), 0);
		redir_info->fd_out = -2;
	}
	close(fd);
	return(1);
}
int	open_files(t_red *redir, t_red_info *redir_info)
{
	int fd;

	while (redir)
	{
		if (redir->is_ambegious)
		{
			write(2, "msh-0.1$ : ambiguous redirect\n", 31);
			return(free(redir_info->herdc_content),exit(1), 0);
		}
		else if (redir->red_type == RED_IN)
		{
			fd = open(redir->red_file, O_RDWR);
			if (fd < 0)
				return(perror("msh-0.1$ "),free(redir_info->herdc_content), exit(1) ,0);
			redir_info->red_input = redir->red_file;
		}
		else if (!red_out(redir, redir_info))
			return (free(redir_info->herdc_content), exit(1), 0);
		redir = redir->next;
	}
	return (1);
}

void implement_heredoc(t_red *redr, t_red_info *red_info, t_env *env)
{
	t_red *cur;

	cur = redr;
	while(redr)
	{
		if (redr->red_type == HERE_DOC)
			red_info->number_of_herd++;
		redr = redr->next;
	}
	if (red_info->number_of_herd)
	{
		red_info->red_input = NULL;
		heredoc(cur,red_info, env);
		if (!red_info->herdc_content)
			red_info->herdc_content = ft_strdup("");
	}
}
int implement_redirections(t_red *redr, t_red_info *red_info, t_env *env)
{
	red_info->number_of_herd = 0 ;
	red_info->red_out = NULL;
	red_info->red_input = NULL;
	red_info->fd_out = -5;
	
	implement_heredoc(redr, red_info, env);
	open_files(redr, red_info);
	if (red_info->fd_out == -2)
		red_info->fd_out = open(red_info->red_out, O_CREAT | O_RDWR | O_APPEND);
	else if (red_info->fd_out == -3)
		red_info->fd_out = open(red_info->red_out, O_CREAT | O_RDWR | O_TRUNC);
	if (red_info->fd_out == -1)
		return(perror("msh-0.1$ "), 0);
	if (red_info->red_input)
	{
		red_info->fd_inp = open(red_info->red_input, O_RDWR);
		if (red_info->fd_inp < 0)
			return(perror("msh-0.1$ "),  0);
		if (red_info->herdc_content)
		{
			red_info->red_input = NULL;
			close(red_info->fd_inp);
			return (1);
		}
	}
	return (1);
}

