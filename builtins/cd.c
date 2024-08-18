#include "../init.h"

void ft_cd(char *path)
{
	//write(1, "kl\n", 3);
	if (!path)
	{
		if (chdir(getenv("HOME")))
			perror("cd");
	}
	else if (chdir(path))
		perror("cd");
}
