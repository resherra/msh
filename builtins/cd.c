#include "../init.h"

int ft_cd(char *path)
{
	if (!path)
	{
		if (chdir(getenv("HOME")))
		{
			perror("cd");
			return (1);
		}
	}
	else if (chdir(path))
	{
		perror("cd");
		return (1);
	}
	return (0);
}
