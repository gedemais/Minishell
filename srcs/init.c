#include "../includes/minishell.h"

char	**ft_cpy_env(char **environ)
{
	char	**env;
	int	i;

	i = 0;
	while (environ[i] != NULL)
		i++;
	if (!(env = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (environ[i] != NULL)
	{
		if (!(env[i] = ft_strdup(environ[i])))
			return (NULL);
		i++;
	}
	env[i] = NULL;
	return (env);
}
