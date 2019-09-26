/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:25 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 16:24:28 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	chdir_errors(char **av)
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
	return (0);
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
	t_env_lst	*pwd;

	pwd = NULL;
	if ((!(pwd = get_var(env->env, "PWD"))
		&& (*status = -1)) || (av[1] && av[2]
		&& (*status = 2)))
		return (NULL);
	if (!(dest = NULL) && !av[1])
	{
		if (!(dest = cd_home(env, status)))
			return (NULL);
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
	if (chdir(path) == -1 && chdir_errors(av) == 0)
	{
		free(path);
		return (1);
	}
	return (replace_paths(env, pwd, path) == 0 ? 0 : -1);
}
