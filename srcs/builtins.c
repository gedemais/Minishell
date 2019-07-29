#include "minishell.h"

static inline int	ft_pwd(t_env *env)
{
	char	*buff;
	size_t	buff_size;

	(void)env;
	buff_size = 1024;
	if (!(buff = ft_strnew(buff_size)))
		return (-1);
	while (getcwd(buff, buff_size) == NULL)
	{
		if (errno != ERANGE)
			return (-1);
		buff_size *= 2;
		if (!(buff = ft_strrealloc(buff, buff_size)))
			return (-1);
	}
	ft_putendl(buff);
	return (0);
}

int		builtins(t_env *env)
{
	unsigned int	i;

	i = 0;
	if (ft_strcmp(env->split[0], "exit") == 0)
		exit (EXIT_SUCCESS);
	else if (ft_strcmp(env->split[0], "pwd") == 0)
		return (ft_pwd(env));
//	else if (ft_strcmp(env->split[0], "env") == 0)
//		return (ft_env(env));
	return (-1);
}
