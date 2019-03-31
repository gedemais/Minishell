#include "../includes/minishell.h"

static char	*ft_find_bin(char *dir, char *bin)
{
	char	*tmp;
	char	*path;
	int		ret;

	if (!(tmp = ft_strjoin(dir, "/")))
		return (NULL);
	if (!(path = ft_strjoin(tmp, bin)))
		return (NULL);
	ret = access(path, X_OK);
	if (ret == 0)
		return (path);
	return (NULL);
}

char		*ft_binarys(char *cmd, char **env)
{
	char	**path;
	char	*dest;
	int		bins;
	int		i;

	i = 0;
	dest = NULL;
	bins = ft_find_var(env, "PATH");
	while (env[bins][i] && env[bins][i - 1] != '=')
		i++;
	if (!(path = ft_strsplit(&env[bins][i], ':')))
		return (NULL);
	i = 0;
	while (path[i])
	{
		if ((dest = ft_find_bin(path[i], cmd)))
			break ;
		i++;
	}
	return (dest);
}
