/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_bis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:46:29 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 16:20:12 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_less(t_env *env)
{
	t_env_lst	*oldpwd;
	char		*path;

	if (!(oldpwd = get_var(env->env, "OLDPWD")))
	{
		ft_putstr_fd("cd: no previous path found.\n", 2);
		return (NULL);
	}
	ft_putendl(oldpwd->val);
	if (!(path = ft_strdup(oldpwd->val)))
		return (NULL);
	return (path);
}

char	*cd_home(t_env *env, int *status)
{
	t_env_lst	*home;
	char		*dest;

	if (!(home = get_var(env->env, "HOME"))
		|| (!(dest = ft_strdup(home->val))))
	{
		*status = -1;
		ft_putstr_fd("cd: No home found.\n", 2);
		return (NULL);
	}
	return (dest);
}

int		secure_pwd(t_env *env)
{
	t_env_lst	*pwd;

	if (get_var(env->env, "PWD"))
		return (0);
	if (!(pwd = get_var(env->env, "PWD"))
		&& !(pwd = get_pwd()))
		return (-1);
	if (!env->env)
		env->env = pwd;
	else if (t_env_lst_pushfront(&env->env, pwd) != 0)
		return (-1);
	return (0);
}

bool	check_white(char **av)
{
	unsigned int	i;
	unsigned int	j;
	bool			ws;

	i = 0;
	j = 0;
	ws = true;
	while (av[i])
		i++;
	i--;
	while (av[i][j])
	{
		if (ft_is_whitespace(av[i][j]) == 0)
			ws = false;
		j++;
	}
	return (ws);
}

int		replace_paths(t_env *env, t_env_lst *pwd, char *path)
{
	if (replace_value(env->env, "OLDPWD", pwd->val) == -1
		|| replace_value(env->env, "PWD", path) == -1)
		return (-1);
	free(path);
	return (0);
}
