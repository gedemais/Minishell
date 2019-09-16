#include "minishell.h"

int	parser(t_env *env)
{
	int	ret;

	if ((ret = builtins(env, env->input)) != 0)
	{
		if (ret == -1)
			return (1);
		return (0);
	}
	ft_putstr_fd("command not found\n", 2);
	return (1);
}
