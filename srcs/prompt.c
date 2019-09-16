#include "minishell.h"



/*
static inline char	*make_path(char *path)
{
	unsigned int	i;

	i = 0;
	while (path[i])
		i++;
	while (path[i] != '/' && i > 0)
		i--;
	return (&path[i + 1]);
}*/

int	prompt(t_env *env, int state)
{
	(void)env;
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('$');
	ft_putchar('{');
	ft_putstr(STOP);
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
	return (0);
}
