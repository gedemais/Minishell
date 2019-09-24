/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:25 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/24 15:10:32 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	chdir_errors(char **av)
{
	if (errno == EACCES)
	{
		ft_putstr_fd(CD_ERR_EACCES, 2);
		ft_putendl_fd(av[1], 2);
	}
	else if (errno == ENOENT)
	{
		ft_putstr_fd(CD_ERR_ENOENT, 2);
		ft_putendl_fd(av[1], 2);
	}
}

static inline int	cd_errors(int id)
{
	if (id == -1)
		return (-1);
	if (id == 2)
		ft_putstr_fd(CD_ERR_TMARGS, 2);
	return (0);
}

static inline char	*get_dots(char *pwd, char *dots)
{
	char			*dest;
	size_t			len;
	unsigned int	i;

	i = 0;
	if (!(dest = ft_strdup(pwd)))
		return (NULL);
	len = ft_strlen(dots);
	if (len == 1)
		return (dest);
	while (i < len - 1 && ft_strlen(dest) >= 1)
	{
		dest = trim_path_end(dest);
		i++;
	}
	if (!dest[0])
		dest[0] = '/';
	return (dest);
}

static inline char	*make_cd_path(t_env *env, char **av, int *status)
{
	char		*dest;
	t_env_lst	*home;
	t_env_lst	*pwd;

	pwd = NULL;
	if ((!(pwd = get_var(env->env, "PWD"))
		&& (*status = -1)) || (av[1] && av[2]
		&& (*status = 2)))
		return (NULL);
	if (!(dest = NULL) && !av[1])
	{
		if (!(home = get_var(env->env, "HOME"))
			|| (!(dest = ft_strdup(home->val)) && (*status = -1)))
		{
			ft_putstr_fd("cd: No home found.\n", 2);
			return (NULL);
		}
	}
	else if (av[1] && is_dots(av))
		return (get_dots(pwd->val, av[1]));
	else if (av[1][0] == '/' && (!(dest = ft_strdup(av[1]))
		&& (*status = -1)))
		return (NULL);
	else if (av[1][0] != '/' && !(dest = re_assemble(pwd->val, "/", av[1]))
		&& (*status = -1))
		return (NULL);
	return (dest);
}

static inline int	secure_pwd(t_env *env)
{
	t_env_lst	*pwd;

	if (get_var(env->env, "PWD"))
		return (0);
	if (!(pwd = get_var(env->env, "PWD")) && !(pwd = get_pwd()))
		return (-1);
	if (!env->env)
		env->env = pwd;
	else if (t_env_lst_pushfront(&env->env, pwd) != 0)
		return (-1);
	return (0);
}

static inline char	*cd_less(t_env *env)
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

int					ft_cd(t_env *env, char **av)
{
	t_env_lst	*pwd;
	char		*path;
	int			ret;

	ret = 0;
	if (secure_pwd(env) != 0 || !(pwd = get_var(env->env, "PWD")))
		return (-1);
	if (av[1] && av[1][0] == '-' && !av[1][1] && !av[2])
	{
		if (!(path = cd_less(env)))
			return (1);	
	}
	else if (!(path = make_cd_path(env, av, &ret)) || ret != 0)
	{
		if (path)
			free(path);
		return (cd_errors(ret) ? -1 : 1);
	}
	if (chdir(path) == -1)
	{
		chdir_errors(av);
		free(path);
		return (1);
	}
	if (replace_value(env->env, "OLDPWD", pwd->val) == -1
		|| replace_value(env->env, "PWD", path) == -1)
		return (-1);
	free(path);
	return (0);
}
