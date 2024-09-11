#include "../init.h"

static int	up_date(t_env *env, char **old, char **curr, char *old_path)
{
	while (env)
	{
		if (!ft_strcmp(env->key, "PWD"))
			curr = &env->value;
		else if (!ft_strcmp(env->key, "OLDPWD"))
			old = &env->value;
		if (old && curr)
			break;
		env = env->next;
	}
	if (curr)
	{
		free(*curr);
		*curr = getcwd(NULL, 0);
		if (*curr == NULL)
			return (perror("msh-0.1$ "), 1);
	}
	if (old)
	{
		free(*old);
		*old = old_path;
	}
	return (1);
}

int ft_cd(char *path, t_env *env)
{
	char **old;
	char **curr;
	char *old_Path;

	old = NULL;
	curr = NULL;
	old_Path = getcwd(NULL, 0);
	if (!old_Path)
		return (perror("msh-0.1$ "), 1);
	if (!path)
	{
		if (chdir(getenv("HOME")))
			return (perror("msh-0.1$: cd"), 1);
	}
	else if (chdir(path))
		return (perror("cd"), 1);
	up_date(env, old, curr, old_Path);
	return (0);
}
