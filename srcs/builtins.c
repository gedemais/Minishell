#include "../includes/minishell.h"

static inline void	ft_exit(t_env *env)
{
	env = ft_free_env(env);
	exit (EXIT_SUCCESS);
}

t_env			*ft_cd(t_env *env)
{
	char	**path;

	if (!(path = ft_strsplit(env->input, ' ')))
		return (NULL);
	if (access(env->input, F_OK) == -1)
	{
		if (errno == EACCES)
			return (NULL);
	}
	else if (chdir(env->input))
}

int			ft_builtins_tree(t_env *env)
{
	if (ft_strncmp(env->input, "exit", 4) == 0
		|| ft_strncmp(env->input, "exit ", 5) == 0)
		ft_exit(env);
	else if (ft_strncmp(env->input, "cd", 2) == 0 || ft_strncmp(env->input, "cd ", 2) == 0)
	{
		if (!(env = ft_cd(env))
			return (-1);
		return (1);
	}
	else if (ft_strncmp(env->input, "echo ", 5) == 0)
		return (1);
	else if (ft_strncmp(env->input, "env ", 5) == 0)
		return (1);
	else if (ft_strncmp(env->input, "setenv ", 5) == 0)
		return (1);
	else if (ft_strncmp(env->input, "unsetenv ", 5) == 0)
		return (1);
	return (0);
}
