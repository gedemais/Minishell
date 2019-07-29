#include "minishell.h"

static inline unsigned int	ft_tablen(char **tab)
{
	unsigned int	ret;

	ret = 0;
	while (tab[ret])
		ret++;
	return (ret);
}

static inline char		**tab_dup(char **dest, char **src)
{
	unsigned int	i;

	i = 0;
	if (!(dest = (char**)malloc(sizeof(char*) * (ft_tablen(src) + 1))))
		return (NULL);
	while (src[i])
	{
		if (!(dest[i] = ft_strdup(src[i])))
			return (NULL);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}

int				init_sh(t_env *env, char **environment)
{
	if (!(env->env = tab_dup(env->env, environment)))
		return (-1);
	ft_putstr(L_GREEN);
	ft_putendl("Minishell by gedemais - 2019\n");
	return (0);
}
