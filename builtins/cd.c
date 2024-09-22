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
	return (0);
}

void search_path(t_env *env, char **home)
{
	*home = NULL;
	while (env)
	{
		if (!ft_strcmp(env->key, "HOME"))
		{
			*home = env->value;
			break;
		}
		env = env->next;
	}
}
int ft_cd(char *path, t_env *env)
{
	char	**old;
	char	**curr;
	char	*old_Path;
	char	*home_path;

	search_path(env, &home_path);
	old = NULL;
	curr = NULL;
	old_Path = getcwd(NULL, 0);
	if (!old_Path)
		return (perror("msh-0.1$ "), 1);
	if (!path)
	{
		if (home_path == NULL || chdir(home_path))
			return (printf("msh-0.1$: HOME not set\n"), 1);
	}
	else if (chdir(path))
		return (perror("cd"), 1);
	return (up_date(env, old, curr, old_Path));
}
