#include "minishell.h"

static inline int	get_var_index(char **env, const char *var)
{
	size_t		len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return ((int)i);
		i++;
	}
	return (-1);
}

static inline char	*make_path(char *path)
{
	unsigned int	i;

	i = 0;
	while (path[i])
		i++;
	while (path[i] != '/' && i > 0)
		i--;
	return (&path[i + 1]);
}

int	prompt(t_env *env, int state)
{
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('{');
	ft_putstr(STOP);
	ft_putstr(make_path(env->env[get_var_index(env->env, "PWD")]));
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
	return (0);
}
