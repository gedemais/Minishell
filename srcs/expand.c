/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:43 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/23 14:02:39 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	*expand_var(t_env *env, char *base, char *name, int j)
{
	t_env_lst		*var;
	char			*dest;
	unsigned int	size;

	if (!(var = get_var(env->env, name)))
		return (base);
	size = (unsigned int)(ft_strlen(base) + ft_strlen(var->val));
	if (!(dest = ft_strnew(size)))
		return (NULL);
	ft_strncpy(dest, base, (size_t)j);
	ft_strcat(dest, var->val);
	ft_strcat(dest, &base[j + (int)ft_strlen(name) + 1]);
	free(base);
	return (dest);
}

static inline char	*expand_tilde(t_env *env, char *base, int j)
{
	t_env_lst		*var;
	char			*dest;

	if (!(var = get_var(env->env, "HOME")))
		return (base);
	if (j == 0 && !base[j + 1])
		return (ft_strdup(var->val));
	else if (j == 0 && base[j + 1])
	{
		if (!(dest = ft_strjoin(var->val, &base[1])))
			return (NULL);
		if (access(dest, X_OK) != 0)
		{
			ft_putstr_fd("minishell: no such user or named directory: ", 2);
			ft_putendl_fd(&base[1], 2);
			free(dest);
			return (NULL);
		}
		free(base);
		return (dest);
	}
	return (base);
}

char				**expansions(t_env *env, char **split)
{
	char			*tmp;
	int				i;
	int				j;

	i = -1;
	while (split[++i] && (j = 0) == 0)
		while (split[i][j])
		{
			if (!(tmp = ft_strduptil(&split[i][j + 1], '$')))
				return (NULL);
			if (split[i][j] == '$' && split[i][j + 1] && get_var(env->env, tmp))
			{
				if (!(split[i] = expand_var(env, split[i], tmp, j)))
					return (NULL);
				free(tmp);
				j = 0;
				continue ;
			}
			else if (split[i][j] == '~' && j == 0
				&& !(split[i] = expand_tilde(env, split[i], j)))
				return (NULL);
			free(tmp);
			j++;
		}
	return (split);
}
