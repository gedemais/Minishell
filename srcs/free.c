#include "../includes/minishell.h"

t_env	*ft_free_env(t_env *env)
{
	if (env->input)
	{
		ft_strdel(&(env->input));
		env->input = NULL;
	}
	return (env);
}
