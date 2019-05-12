#include "../includes/minishell.h"

int	ft_parser(t_env *env)
{
	int	ret;

	ret = 0;
	if ((ret = ft_builtins_tree(env)) == 1)
		return (0);
	else if (ret == -1)
		return (ret);
	return (0);
}
