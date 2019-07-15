#include "../includes/minishell.h"

static inline void	ft_exit(t_env *env)
{
	ft_free_env(env->env);
	exit (EXIT_SUCCESS);
}

static inline int	ft_pwd(void)
{
	char	*path;
	int	i;

	i = 1;
	if (!(path = (char*)malloc(sizeof(char) * (i * 1024))))
		return (-1);
	while (!(getcwd(path, (i * 1024))))
	{
		i++;
		if (!(path = ft_strrealloc(path, (i * 1024))))
			return (-1);
	}
	ft_putstr(path);
	ft_putchar('\n');
	return (0);
}

int			ft_builtins_tree(t_env *env)
{
	static char	*builtins[NB_BUILTINS] = {"exit", "env", "setenv"}
	if (ft_strcmp(env->split[0], "exit") == 0)
		ft_exit(env);
	else if (ft_strcmp(env->split[0], "env") == 0)
	{
		if (ft_env(env->env) == -1)
			return (-1);
		return (1);
	}
	else if (ft_strcmp(env->split[0], "setenv") == 0)
	{
		if (!(env = ft_setenv(env, env->split)))
			return (-1);
		return (1);
	}
	else if (ft_strcmp(env->split[0], "unsetenv") == 0)
	{
		if (!(env = ft_unsetenv(env, env->split)))
			return (-1);
		return (1);
	}
	else if (ft_strcmp(env->split[0], "pwd") == 0)
	{
		if (ft_pwd() == -1)
			return (-1);
		return (1);
	}
	return (0);
}
