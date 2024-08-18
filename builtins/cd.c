#include "../init.h"

void ft_cd(char *path)
{
	if (!path)
	{
		if (chdir(getenv("HOME")))
			perror("cd");
	}
	else if (chdir(path))
		perror("cd");
}
