#include "../includes/minishell.h"

static inline int	ft_cut_path(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (str[i] != '/')
		i--;
	return (i + 1);
}

void		ft_prompt(t_env *env, int mode)
{
	char	*path;

	ft_putstr((mode == 0) ? L_GREEN : L_RED);
	ft_putstr("${");
	ft_putstr(STOP);
	if (!(path = ft_get_var_val(env, "PWD")))
		mode = 1;
	else if (ft_strcmp(path, ft_get_var_val(env, "HOME")) != 0)
	{
		ft_putstr(GRA);
		ft_putstr(&path[ft_cut_path(path)]);
		ft_putstr(STOP);
	}
	else
		ft_putchar('~');
	ft_putstr((mode == 0) ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
}
