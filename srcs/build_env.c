/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:02 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 19:03:42 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst				*get_pwd(void)
{
	t_env_lst		*pwd;
	char			*path;
	char			*var;
	unsigned int	size;

	size = 1024;
	if (!(path = ft_strnew(size)))
		return (NULL);
	while (!getcwd(path, size))
	{
		free(path);
		size *= 2;
		if (!(path = ft_strnew(size)))
			return (NULL);
	}
	if (!(var = re_assemble("PWD", "=", path)))
		return (NULL);
	free(path);
	if (!(pwd = t_env_lstnew(var)))
	{
		free(var);
		return (NULL);
	}
	free(var);
	return (pwd);
}

static inline t_env_lst	*get_home(void)
{
	t_env_lst		*home;
	struct passwd	*entry;
	char			*var;
	char			*path;

	if (!(entry = getpwuid(getuid())))
		return (NULL);
	if (!(path = ft_strjoin("/Users/", entry->pw_name)))
		return (NULL);
	if (access(path, F_OK) == -1)
	{
		free(path);
		return (NULL);
	}
	if (!(var = ft_strjoin("HOME=", path)))
		return (NULL);
	free(path);
	if (!(home = t_env_lstnew(var)))
		return (NULL);
	free(var);
	return (home);
}

static inline t_env_lst	*load_var(t_env_lst **lst, t_env_lst *var)
{
	if (!(*lst))
		*lst = var;
	else if (t_env_lst_pushfront(lst, var) != 0)
		return (NULL);
	return (*lst);
}

t_env_lst				*build_env(t_env *env)
{
	t_env_lst	*var;
	bool		all;

	all = (env->env) ? false : true;
	if ((!get_var(env->env, "PWD") || all))
	{
		if (!(var = get_pwd())
			|| !(env->env = load_var(&env->env, var)))
			return (NULL);
	}
	if ((!get_var(env->env, "HOME") || all))
	{
		if (!(var = get_home())
			|| !(env->env = load_var(&env->env, var)))
			return (env->env);
	}
	if ((!get_var(env->env, "PATH") || all))
		if (!(var = t_env_lstnew(B_PATH))
			|| !(env->env = load_var(&env->env, var)))
			return (NULL);
	return (env->env);
}
