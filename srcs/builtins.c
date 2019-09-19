#include "minishell.h"

static inline int	ft_exit(t_env *env)
{
	(void)env;
	exit(EXIT_FAILURE);
}

static inline int	ft_env(t_env *env)
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

int	builtins(t_env *env)
{
	char	*b_names[NB_BUILTINS] = {"env", "setenv", "unsetenv", "exit",
					"echo", "cd"};
	int	(*b_func[NB_BUILTINS])(t_env*) = {ft_env, /*ft_setenv*/NULL,
					/*ft_unsetenv*/NULL, ft_exit, /*ft_echo*/NULL, /*ft_cd*/NULL};
	unsigned int	i;
	int		ret;

	i = 0;
	while (i < NB_BUILTINS)
	{
		if (ft_strcmp(b_names[i], env->split[0]) == 0)
		{
			ret = b_func[i](env);
			if (ret == -1)
				return (-1);
			return (ret == 0 ? 1 : 2);
		}
		i++;
	}
	return (0);
}
