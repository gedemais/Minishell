#include "../includes/minishell.h"

void	ft_free_splits(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		ft_strdel(&split[i]);
		i++;
	}
	free(split);
}

static inline int	ft_isin(char *str, char c)
{
	int	ret;
	int	i;

	i = -1;
	ret = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_parser(t_env *env)
{
	bool	r_val;
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	r_val = false;
	ft_isin(env->input, ' ');
	if (env->input[0] == '\0')
		return (1);
	if (!(env->semisplit = ft_strsplit(env->input, ';')))
		return (-1);
	while (env->semisplit[i])
	{
		if (!(env->split = ft_strsplit(env->semisplit[i], ' ')))
			return (-1);
		if ((ret = ft_builtins_tree(env)) == 1 && ++i)
			continue ;
		else if ((ret = ft_binarys(env, env->split[0], env->split)) == 1 && ++i)
			continue ;
		else if (ret == -1)
			return (-1);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(env->split[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			r_val = true;
		}
		i++;
	}
	ft_free_splits(env->semisplit);
	return ((r_val) ? 1 : 0);
}
