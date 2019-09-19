#include "minishell.h"

static inline int	ft_exit(t_env *env)
{
	(void)env;
	exit(EXIT_SUCCESS);
}

static inline int	ft_echo(t_env *env)
{
	(void)env;
	return (0);
}
static inline int	ft_cd(t_env *env)
{
	(void)env;
	return (0);
}

int	builtins(t_env *env, char *input)
{
	char			*b_names[NB_BUILTINS] = {"exit", "env", "setenv",
						"unsetenv", "echo", "cd"};
	int				(*b_funcs[NB_BUILTINS])(t_env*) = {ft_exit, ft_env,
						ft_setenv, ft_unsetenv, ft_echo, ft_cd};
	char			**split;
	unsigned int	i;

	i = 0;
	if (!(split = ft_strsplit(input, ' ')))
		return (-1);
	if (!split || !split[0])
		return (0);
	while (i < NB_BUILTINS)
	{
		if (ft_strcmp(b_names[i], split[0]) == 0)
		{
			if (b_funcs[i](env) != 0)
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}
