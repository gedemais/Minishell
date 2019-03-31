#include "../includes/minishell.h"

int	ft_find_var(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
