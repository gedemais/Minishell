#include "../includes/minishell.h"

int	ft_ms_lstlen(t_envi *env)
{
	t_envi	*tmp;
	int	ret;

	ret = 0;
	tmp = env;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);

}

char	**ft_refresh_env(t_envi *env)
{
	char	**new;
	t_envi	*tmp;
	int	i;

	i = 0;
	tmp = env;
	if (!(new = (char**)malloc(sizeof(char*) * (ft_ms_lstlen(env) + 2))))
		return (NULL);
	while (tmp)
	{
		if (!(new[i] = (char*)malloc(sizeof(char) * (ft_strlen(tmp->name) + ft_strlen(tmp->value) + 2))))
			return (NULL);
		new[i] = ft_strcpy(new[i], tmp->name);
		new[i] = ft_strcat(new[i], "=");
		new[i]= ft_strcat(new[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	ft_exec(t_env *env, char *bin, char **params)
{
	char	**environment;
	pid_t	id;

	if (!(environment = ft_refresh_env(env->env)))
		return (-1);
	if ((id = fork()) == 0)
		execve(bin, params, environment);
	else
		waitpid(id, NULL, 0);
	ft_free_splits(environment);
	return (0);
}

char	*ft_make_path(char *rep, char *cmd)
{
	char	*dest;
	char	*s_rep;

	if (rep[ft_strlen(rep) - 1] != '/')
	{
		if (!(s_rep = ft_strjoin(rep, "/")))
			return (NULL);
	}
	else if (!(s_rep = ft_strdup(rep)))
		return (NULL);
	if (!(dest = ft_strjoin(s_rep, cmd)))
		return (NULL);
	ft_strdel(&s_rep);
	return (dest);
	
}

char	*ft_find_bin(t_env *env, char *cmd)
{
	char	**bins;
	char	*paths;
	char	*path;
	int	i;

	i = 0;
	ft_env(env->env);
	if (!(paths = ft_get_var_val(env, "PATH")))
		return (NULL);
	if (!(bins = ft_strsplit(paths, ':')))
		return (NULL);
	ft_strdel(&paths);
	while (bins[i])
	{
		if (!(path = ft_make_path(bins[i], cmd)))
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		else
			ft_strdel(&path);
		i++;
	}
	if (ft_strncmp(cmd, "./", 2) == 0)
		if (access(cmd, F_OK) == 0)
			return (cmd);
	return (NULL);
}

int	ft_binarys(t_env *env, char *cmd, char **params)
{
	char	*bin_path;

	ft_env(env->env);
	if (!(bin_path = ft_find_bin(env, cmd)))
		return (0);
	else
	{
		(void)params;
	//	ft_exec(env, bin_path, params);
		ft_strdel(&bin_path);
		return (1);
	}
	ft_env(env->env);
	return (0);
}
