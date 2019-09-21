#include "minishell.h"
/*
static inline char	*expand_var(t_env *env, char *base, unsigned int j)
{
	t_env_lst	*var;
	char		*dest;

	if (!(var = get_var(env->env, &base[j])))
		return (base);
}

static inline char	*expand_tild(char *base)
{
	
}

char	**expansions(t_env *env, char **split)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (split[i][j] == '$' && split[i][j + 1]
				&& get_var(env->env, &split[i][j + 1]) &&
				!(split[i] = expand_var(env, split[i], j + 1)))
				return (NULL);
			else if (split[i][j] == '~' && j == 0
				&& !(split[i] = expand_tild(split[i])))
				return (NULL);
			j++;
		}
		i++;
	}
	return (split);
}*/
