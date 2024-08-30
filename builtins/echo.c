#include "../init.h"

int ft_echo(char **str)
{
	char	**args;
	int		option;

	option = 1;
	args = str + 1;

	if (*args && !strcmp(str[1], "-n"))
	{
		option = 0;
		args = str + 2;
	}
	
	while (*args)
	{
		write(STDOUT_FILENO, *args, ft_strlen(*args));
		args++;
		if (*args)
			write(STDOUT_FILENO, " ", 1);
	}
	
	if (option)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
