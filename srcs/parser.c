#include "minishell.h"

static inline void	free_ctab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int		parser(t_env *env, char *line)
{
	unsigned int	i;
	int		ret;

	i = 0;
	if (!(env->semisplit = ft_strsplit(line, ';')))
		return (-1);
	while (env->semisplit[i])
	{
		if (!(env->split = ft_strsplit(line, ' ')))
			return (-1);
		if ((ret = builtins(env)) >= 0)
			return (ret);
		free_ctab(env->split);
		i++;
	}
	free_ctab(env->semisplit);
	return (0);
}
