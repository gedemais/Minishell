#include "../includes/minishell.h"

char	*ft_binarys(char *cmd, char **env)
{
	char	**path;
	char	*dest;
	int	bins;
	int	i;

	i = 0;
	(void)cmd;
	dest = NULL;
	bins = ft_find_var(env, "PATH");
	while (env[bins][i] && env[bins][i - 1] != '=')
		i++;
	if (!(path = ft_strsplit(&env[bins][i], ':')))
		return (NULL);
	i = 0;
	while (path[i])
	{
		ft_putendl(path[i]);
		i++;
	}
	return (dest);
}
