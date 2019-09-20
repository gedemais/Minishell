#include "minishell.h"

static inline int	unsetenv_cases(t_env_lst *env, char **av)
{
	t_env_lst	*tmp;
	t_env_lst	*tmp2;

	tmp = env;
	tmp2 = env->next;
	if (ft_strcmp(env->name, av[1]) == 0)
 	{
		env = env->next;
		free(tmp);
		return (1);
	}
	while (tmp2->next)
	{
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if (ft_strcmp(tmp2->name, av[1]) == 0)
	{
		tmp->next = NULL;
		free(tmp2);
		return (1);
	}
	return (0);
}

int	ft_unsetenv(t_env *env, char **av)
{
	t_env_lst	*tmp;
	t_env_lst	*tmp2;
	unsigned int	i;

	i = 0;
		print_env(env->env);
		printf("-----------------------------------------\n");
	if (unsetenv_cases(env->env, av))
		return (0);
	while (av[++i])
	{
		tmp = env->env;
		tmp2 = env->env->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp2->name, av[i]) == 0)
			{
		print_env(env->env);
		printf("-----------------------------------------\n");
				tmp2 = tmp2->next;
				free(tmp->next);
				tmp->next = tmp2;
		print_env(env->env);
		printf("-----------------------------------------\n");
				return (0);
			}
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return (1);
}
