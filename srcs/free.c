#include "../includes/minishell.h"

void	ft_free_env(t_envi *env)
{
	if (env->next)
		ft_free_env(env->next);
	free(env);
}
