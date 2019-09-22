/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:38 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 18:34:57 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*find_binary(t_env *env, char **av)
{
	char			*dest;
	t_env_lst		*path;
	char			**p;
	unsigned int	i;

	i = 0;
	if (access(av[0], X_OK) == 0)
		return (ft_strdup(av[0]));
	if (!(path = get_var(env->env, "PATH"))
		|| !(p = ft_strsplit(path->val, ":")))
		return (NULL);
	while (p[i])
	{
		if (!(dest = re_assemble(p[i], "/", av[0])) && !free_ctab(p))
			return (NULL);
		if (access(dest, X_OK) == 0)
		{
			free_ctab(p);
			return (dest);
		}
		free(dest);
		i++;
	}
	free_ctab(p);
	return (NULL);
}

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
}

char				**refresh_env(t_env_lst *env, char **environment)
{
	char			**new;
	t_env_lst		*tmp;
	unsigned int	len;
	unsigned int	i;

	i = 0;
	tmp = env;
	len = env_len(env);
	if (environment)
		free_ctab(environment);
	if (!(new = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	while (i < len && tmp)
	{
		if (!(new[i] = re_assemble(tmp->name, "=", tmp->val)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

int					exec_binary(t_env *env)
{
	int				status;
	char			*path;
	pid_t			pid;
	unsigned int	i;

	i = 0;
	status = 0;
	if (!(path = find_binary(env, env->split)))
		return (2);
	if (!(env->environment = refresh_env(env->env, env->environment)))
		return (-1);
	if ((pid = create_process()) == -1)
		return (-1);
	if (pid == 0)
		execve(path, env->split, env->environment);
	if (wait(&status) == -1)
		return (-1);
	free(path);
	return (WIFEXITED(status));
}
