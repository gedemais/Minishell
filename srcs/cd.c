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

static inline int	cd_cases(t_env *env, char **av, bool *prev)
{
	t_env_lst	*pwd;
	t_env_lst	*oldpwd;
	t_env_lst	*home;

	if (!(pwd = get_var(env->env, "PWD"))
		|| !(oldpwd = get_var(env->env, "OLDPWD")))
		return (1);
	if ((!av[1] || !av[1][0]))
	{
		if (!(home = get_var(env->env, "HOME")))
			return (1);
		replace_value(env->env, "OLDPWD", pwd->val);
		replace_value(env->env, "PWD", home->val);
		*prev = true;
		return (0);
	}
	if (ft_strcmp(av[1], ".") == 0)
	{
		replace_value(env->env, "OLDPWD", pwd->val);
		*prev = true;
		return (0);
	}
	if (ft_strcmp(av[1], "..") == 0)
	{
		replace_value(env->env, "OLDPWD", pwd->val);
		pwd->val = trim_path_end(pwd->val);
		*prev = true;
		return (0);
	}
	return (0);
}

static inline void	cd_errors(char **av)
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

int	ft_cd(t_env *env, char **av)
{
	t_env_lst	*pwd;
	char		*path;
	bool		prev;

	prev = false;
	path = NULL;
	if (cd_cases(env, av, &prev) || av[2])
		return (1);
	pwd = get_var(env->env, "PWD");
	if (prev && !(path = ft_strdup(pwd->val)))
		return (-1);
	if (!prev && !(path = re_assemble(pwd->val, "/", av[1])))
		return (-1);
	printf("%s\n", path);
	if (chdir(path) == -1)
	{
		cd_errors(av);
		return (1);
	}
	replace_value(env->env, "OLDPWD", pwd->val);
	replace_value(env->env, "PWD", path);
	free(path);
	return (0);
}
