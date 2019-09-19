#include "minishell.h"

unsigned int	env_len(t_env_lst *env)
{
	t_env_lst	*tmp;
	unsigned int	ret;

	tmp = env;
	ret = 0;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

char		*re_assemble(char *s1, char *s2, char *s3)
{
	char	*tmp;
	char	*dest;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	if (!(dest = ft_strjoin(tmp, s3)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (dest);
}
