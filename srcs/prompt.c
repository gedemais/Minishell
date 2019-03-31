#include "../includes/minishell.h"


static int	ft_short_path(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	return (i + 1);
}

void		ft_prompt(char **env, int mode)
{
	int	pos;

	ft_putstr((mode == 0) ? L_GREEN : L_RED);
	ft_putstr("${");
	ft_putstr(STOP);
	if ((pos = ft_find_var(env, "PWD")) == -1)
		(void)env;
	else
	{
		ft_putstr(GRA);
		ft_putstr(&env[pos][ft_short_path(env[pos])]);
		ft_putstr(STOP);
	}
	ft_putstr((mode == 0) ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
}
