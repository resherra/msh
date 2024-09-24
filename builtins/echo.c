#include "../init.h"


int ft_echo(char **str)
{
	int		option;
	int		i;
	int		j;

	i = 1;
	option = 0;
	while (*str && str[i] &&  str[i][0] == '-' && str[i][1] == 'n')
	{
		j = 1;
		while (str[i][j] == 'n')
			j++;
		if (str[i][j] != 0)
			break;
		option = 1;
		i++;
	}
	while (*str && str[i])
	{
		write(STDOUT_FILENO, str[i], ft_strlen(str[i]));
		if (str[++i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!option)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
