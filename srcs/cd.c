#include "minishell.h"

static inline char	*trim_path_end(char *path)
{
	unsigned int	i;

	i = (unsigned int)ft_strlen(path) - 1;
	while (i > 0 && path[i] != '/')
		i--;
	while (path[i])
	{
		path[i] = '\0';
		i++;
	}
	return (path);
}

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

static inline bool	is_dots(char **av)
{
	unsigned int	i;

	i = 0;
	while (av[1][i])
	{
		if (av[1][i] != '.')
			return (false);
		i++;
	}
	return (true);
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
	return (dest);
}

static inline char	*make_cd_path(t_env *env, char **av, int *status)
{
	char		*dest;
	t_env_lst	*home;
	t_env_lst	*pwd;

	pwd = NULL;
	if ((!(home = get_var(env->env, "HOME"))
		|| !(pwd = get_var(env->env, "PWD"))) && (*status = -1))
		return (NULL);
	if (av[1] && av[2] && (*status = 2))
		return (NULL);
	if (av[1] && is_dots(av))
		return (get_dots(pwd->val, av[1]));
	if (!av[1])
	{
		if (!(dest = ft_strdup(home->val)) && (*status = -1))
			return (NULL);
	}
	else if (av[1][0] == '/')
	{
		if (!(dest = ft_strdup(av[1])) && (*status = -1))
			return (NULL);
	}
	else if (!(dest = re_assemble(pwd->val, "/", av[1])) && (*status = -1))
			return (NULL);
	return (dest);
}

int	ft_cd(t_env *env, char **av)
{
	t_env_lst	*pwd;
	char		*path;
	int			ret;

	if (!(pwd = get_var(env->env, "PWD")))
		return (-1);
	if (!(path = make_cd_path(env, av, &ret)) || ret != 0)
		return (cd_errors(ret) ? -1 : 1);
	if (chdir(path) == -1)
	{
		chdir_errors(av);
		return (1);
	}
	if (replace_value(env->env, "OLDPWD", pwd->val) == -1
		|| replace_value(env->env, "PWD", path) == -1)
		return (-1);
	free(path);
	return (0);
}
