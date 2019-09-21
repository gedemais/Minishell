#include "minishell.h"


int		ft_echo(t_env *env, char **av)
{
	unsigned int		i;
	bool				n;

	(void)env;
	i = 1;
	if (!av[1])
	{
		ft_putchar('\n');
		return (0);
	}
	n = (ft_strcmp(av[1], "-n") == 0) ? true : false;
	if (n)
		i++;
	while (av[i])
	{
		ft_putstr(av[i]);
		ft_putchar(' ');
		i++;
	}
	if (!n)
		ft_putchar('\n');
	return (0);
}
