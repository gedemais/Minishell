#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env_lst	*tmp;

	tmp = env->env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putchar('=');
		ft_putendl(tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

static inline int	modify(t_env *env, char *var, char *new_val)
{
	t_env_lst	*tmp;
	unsigned int	i;

	i = 0;
	tmp = env->env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, var) == 0)
		{
			free(tmp->val);
			if (!(tmp->val = ft_strdup(new_val)))
				return (-1);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_setenv(t_env *env)
{
	char		**av;
	unsigned int	i;

	i = 0;
	if (!(av = ft_strsplit(env->input, ' ')))
		return (-1);
	while (av[i])
		i++;
	if (i != 3)
		return (0);
	if (modify(env, av[1], av[2]) == 1)
		return (0);
	
	return (0);
}

int	ft_unsetenv(t_env *env)
{
	(void)env;
	return (0);
}
