#include "minishell.h"



int	parser(t_env *env)
{
//	unsigned int	i;
	int				ret;

//	i = 0;
	if (!env->input || env->input[0] == '\0')
		return (0);
	if ((ret = builtins(env, env->input)) != 0)
		return ((ret == -1) ? 1 : 0);
/*	if (!(env.semisplit = ft_strsplit(env->input, ';')))
		return (1);
	while (env.semisplit[i])
	{
		if ()
		i++;
	}*/
	ft_putstr_fd("command not found\n", 2);
	return (1);
}
