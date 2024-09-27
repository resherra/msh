/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apple <apple@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 21:09:21 by schakkou          #+#    #+#             */
/*   Updated: 2024/09/27 20:38:15 by apple            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init.h"

static int	heredoc(t_red *hrdc, t_red_info *red_info, t_env *env)
{
	char	*input;

	while (hrdc->red_type != HERE_DOC)
		hrdc = hrdc->next;
	while (1)
	{
		input = readline(">");
		if (!input || !ft_strcmp(input, hrdc->red_file))
		{
			red_info->number_of_herd--;
			if (red_info->number_of_herd == 0 && !input)
				return (free(red_info->herdc_content), 0);
			if (red_info->number_of_herd == 0)
				return (free(input), 1);
			hrdc = hrdc->next;
			while (hrdc->red_type != HERE_DOC)
				hrdc = hrdc->next;
		}
		else if (red_info->number_of_herd == 1)
			save_herdoc_data(env, hrdc, input, red_info);
	}
	return (0);
}

int	red_out(t_red *redir, t_red_info *redir_info)
{
	int	fd;

	fd = -1;
	if (redir->red_type == RED_OUT)
	{
		redir_info->red_out = redir->red_file;
		fd = open(redir_info->red_out, O_CREAT | O_RDWR | O_TRUNC,
				S_IWUSR | S_IRUSR);
		if (fd < 0)
			return (perror("msh-0.1$ "), 0);
		redir_info->fd_out = -3;
	}
	else if (redir->red_type == RED_APP)
	{
		redir_info->red_out = redir->red_file;
		fd = open(redir->red_file, O_CREAT | O_RDWR | O_APPEND,
				S_IWUSR | S_IRUSR);
		if (fd < 0)
			return (perror("msh-0.1$ "), 0);
		redir_info->fd_out = -2;
	}
	close(fd);
	return (1);
}

int	open_files(t_red *redir, t_red_info *redir_info)
{
	int	fd;

	while (redir)
	{
		if (redir->is_ambegious)
		{
			write(2, "msh-0.1$ : ambiguous redirect\n", 31);
			return (free(redir_info->herdc_content), exit(1), 0);
		}
		else if (redir->red_type == RED_IN)
		{
			fd = open(redir->red_file, O_RDWR);
			if (fd < 0)
				return (perror("msh-0.1$ "), free(redir_info->herdc_content),
					exit(1), 0);
			redir_info->fd_inp = fd;
			if (redir_info->number_of_herd == 0)
				redir_info->red_input = redir->red_file;
		}
		else if (!red_out(redir, redir_info))
			return (free(redir_info->herdc_content), exit(1), 0);
		redir = redir->next;
	}
	return (1);
}

void	implement_heredoc(t_red *redr, t_red_info *red_info, t_env *env,
		int in_herdc_child)
{
	t_red	*cur;

	cur = redr;
	while (redr)
	{
		if (redr->red_type == HERE_DOC)
			red_info->number_of_herd++;
		redr = redr->next;
	}
	if (red_info->number_of_herd)
	{
		red_info->red_input = NULL;
		if (in_herdc_child)
		{
			if (!heredoc(cur, red_info, env))
				red_info->herdc_content = NULL;
		}
	}
}

int	implement_redirections(t_red *redr, t_red_info *red_info, t_env *env,
		int in_herdc_child)
{
	red_info->number_of_herd = 0;
	red_info->red_out = NULL;
	red_info->red_input = NULL;
	red_info->fd_out = -5;
	implement_heredoc(redr, red_info, env, in_herdc_child);
	if (red_info->nmbr_cmd_herdc != 1 || !in_herdc_child)
	{
		open_files(redr, red_info);
		if (red_info->fd_out == -2)
			red_info->fd_out = open(red_info->red_out,
					O_CREAT | O_RDWR | O_APPEND);
		else if (red_info->fd_out == -3)
			red_info->fd_out = open(red_info->red_out,
					O_CREAT | O_RDWR | O_TRUNC);
		if (red_info->fd_out == -1)
			return (perror("msh-0.1$ "), 0);
	}
	return (1);
}
