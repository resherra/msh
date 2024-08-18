#include "../init.h"


int duplicate_stdin(int fd)
{
	close(fd);
    fd = open("input.txt", O_CREAT | O_RDWR);
    dup2(fd, STDIN_FILENO);
    return ( 1);
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
	}
	else if (herdc->red_type == RED_OUT)
	{
		if (out_fd > 0)
			close(in_fd);
		out_fd = open(herdc->red_file, O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
		if (out_fd < 0)
            return (perror("msh-0.1$ "), false);
		dup2(out_fd, STDOUT_FILENO);
	}
	return(1);
}

static int heredoc(t_red **hrdc)
{
    int     fd;
    char    *input;

    fd = open("input.txt", O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IRUSR);
    if (fd < 0)
        return (0);
    while (1)
    {
        input = readline(">");
        if (!input)
            return(close(fd), allocation_error);
        if ((*hrdc)->red_type == HERE_DOC && !strcmp(input , (*hrdc)->red_file))
        {
            if (!(*hrdc)->next)
                return (free(input), duplicate_stdin(fd));
            (*hrdc) = (*hrdc)->next;
			if ((*hrdc)->red_type != HERE_DOC)
				return(free(input), terminate_red(*hrdc));
        }
        else
        {
            write(fd, input, ft_strlen(input));
            write(fd, "\n", 1);
        }  
    }
}

int	red_append(char *file)
{
	static int	fd;

	if (fd > 0)
		close(fd);
		
	fd = open(file, O_CREAT | O_RDWR | O_APPEND, S_IWUSR | S_IRUSR);
	if (fd < 0)
        return (perror("msh-0.1$ "), false);
	dup2(fd, STDOUT_FILENO);
	return(1);
}

int implement_redirections(t_red *redrctns)
{

    while (redrctns)
	{
		if (redrctns->red_type == HERE_DOC)
			heredoc(&redrctns);
		else if (redrctns->red_type == RED_APP)
			red_append(redrctns->red_file);
		else
			terminate_red(redrctns);
		redrctns = redrctns->next;
	}
	return (1);
}
