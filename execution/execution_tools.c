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

int terminate_red(t_red *herdc)
{
	static int in_fd;
	static int out_fd;

	if (herdc->red_type == RED_IN)
    {
		if (in_fd > 0)
			close(in_fd);
		in_fd = open(herdc->red_file, O_RDWR);
		if (in_fd < 0)
            return (perror("msh-0.1$ "), false);
		dup2(in_fd, STDIN_FILENO);
		//close(in_fd);
	}
	else if (herdc->red_type == RED_OUT)
	{
		if (out_fd > 0)
			close(in_fd);
		out_fd = open(herdc->red_file, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
		if (out_fd < 0)
            return (perror("msh-0.1$ "), false);
		dup2(out_fd, STDOUT_FILENO);
				//close(out_fd);

	}
	return(1);
}


static int heredoc(t_red *hrdc, t_red_info *red_info, int *pid)
{
    char    *input;
	char	*tmp;

	while (hrdc->red_type != HERE_DOC)
		hrdc = hrdc->next;
    while (1)
    {
        input = readline(">");
        if (!input )
			return( 0);	
        if (!strcmp(input , hrdc->red_file))
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
			tmp = red_info->herdc_content;
			red_info->herdc_content = ft_join(red_info->herdc_content, input);
			free(tmp);
		}
    }
	return(0);
}


// int implement_redirections(t_red *redrctns, t_red_info *red_info)
// {
// 	int check_ambg;
// 	t_red *tmp;

// 	tmp = redrctns;
// 	check_ambg = redrctns->is_ambegious;
// 	// while (tmp)
// 	// {
// 	// }
	
//     while (redrctns)
// 	{
// 		if (redrctns->red_type == HERE_DOC)
// 		{
// 			heredoc(&redrctns);
// 			if (check_ambg)
// 			{
// 				write(2, "ambiguous redirect\n", 19);
// 				return (0);
// 			}
// 		}
// 		else if (redrctns->red_type == RED_APP)
// 			red_append(redrctns->red_file);
// 		else
// 			terminate_red(redrctns);
// 		redrctns = redrctns->next;
// 	}
// 	return (1);
// }

int implement_redirections(t_red *redr, t_red_info *red_info, int *pid)
{
//khes redouan yesla7 hadi cat << a < $gxfg
	red_info->number_of_herd = 0 ;
	red_info->red_out = NULL;
	red_info->red_input = NULL;
	red_info->fd_out = -1;
	red_info->error = NULL;
	int fd = -1;
	t_red *cur= redr;
	
	while(redr)
	{
		//write(2, "yes\n", 4);
		if (redr->is_ambegious)
		{
			//write(2, "y\n", 2);
			red_info->error = "msh-0.1$ : ambiguous redirect\n";
		}
		if (redr->red_type == HERE_DOC)
			red_info->number_of_herd++;
		else if (!redr->is_ambegious && redr->red_type == RED_OUT)
		{
			red_info->red_out = redr->red_file;
			 fd = open(red_info->red_out, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
			if (fd < 0)
            	return (perror("msh-0.1$ "), 1);
			red_info->fd_out = -3;
		}
		else if (!redr->is_ambegious && redr->red_type == RED_APP)
		{
			red_info->red_out = redr->red_file;
			 fd = open(redr->red_file, O_CREAT | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
			if (fd < 0)
            return (perror("msh-0.1$ "), 1);
			red_info->fd_out = -2;
		}
		else if (redr->red_type == RED_IN && red_info->number_of_herd == 0)
			red_info->red_input = redr->red_file;
		 close(fd);
		redr = redr->next;
	}
	if (red_info->number_of_herd)
	{
		*pid = -3;
		red_info->red_input = NULL;
		heredoc(cur,red_info, pid);
		if (!red_info->herdc_content)
			red_info->herdc_content = ft_strdup("");
	}
	if (red_info->error)
	{
		write(2, "msh-0.1$ : ambiguous redirect\n", 31);
		return(0);
	}
	if (red_info->fd_out == -2)
		red_info->fd_out = open(red_info->red_out, O_CREAT | O_RDWR | O_APPEND);
	else if (red_info->fd_out == -3)
		red_info->fd_out = open(red_info->red_out, O_CREAT | O_RDWR | O_TRUNC);
	else if (red_info->red_input)
	{
		red_info->fd_inp = open(red_info->red_input, O_RDWR);
	}
	return (1);
}
