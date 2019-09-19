#include "minishell.h"

static inline char	*find_binary(t_env *env, char **av)
{
	char		**paths;
	t_env_lst	*path;
	char		*dest;
	unsigned int	i;

	i = 0;
	if (!(path = get_var(env->env, "PATH"))
		|| !(paths = ft_strsplit(path->val, ':')))
		return (NULL);
	while (paths[i])
	{
		if (!(dest = re_assemble(paths[i], "/", av[0])))
			return (NULL);
		if (access(dest, X_OK) == 0)
		{
			free_ctab(paths);
			return (dest);
		}
		free(dest);
		i++;
	}
	return (NULL);
}
/*
static inline pid_t	create_process(void)
{
	pid_t		pid;

	pid = fork();
	while (pid == -1)
	{
		if (errno != EAGAIN)
			return (-1);
		pid = fork();
	}
	return (pid);
}*/

char			**refresh_env(t_env_lst *env, char **environment)
{
	t_env_lst	*tmp;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	tmp = env;
	len = env_len(env);
	if (environment)
		free_ctab(environment);
	if (!(environment = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (!(environment[i] = re_assemble(tmp->name, "=", tmp->val)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	environment[i] = NULL;
	return (environment);
}

int			exec_binary(t_env *env)
{
	pid_t		pid;
	unsigned int	i;
	char		*path;

	i = 0;
	if (!(path = find_binary(env, env->split)))
		return (2);
	if (!(env->environment = refresh_env(env->env, env->environment)))
		return (-1);
	pid = fork();
	if (pid == 0)
		execve(path, env->split, env->environment);
	if (wait(NULL) == -1)
		return (-1);
	return (1);
}
