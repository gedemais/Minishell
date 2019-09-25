/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:06 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/25 18:49:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	parse_cmd(t_env *env, char *cmd)
{
	int	ret;

	if (!(env->split = ft_strsplit(cmd, " \t"))
		|| !(env->split = expansions(env, env->split)))
		return (-1);
	ret = builtins(env);
	if ((ret == -1 || ret == 1) && !(env->split = free_ctab(env->split)))
		return (ret == -1 ? -1 : 0);
	else if (ret == 2 && !(env->split = free_ctab(env->split)))
		return (1);
	ret = exec_binary(env);
	if ((ret == -1 || ret == 1) && !(env->split = free_ctab(env->split)))
		return (ret == -1 ? -1 : 0);
	else if (ret == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(env->split[0], 2);
		ft_putstr_fd(": command not found.\n", 2);
		env->split = free_ctab(env->split);
		return (1);
	}
	env->split = free_ctab(env->split);
	return (0);
}

static inline char	**make_semisplit(t_env *env)
{
	char			**dest;
	char			*tmp;
	unsigned int	i;

	i = 0;
	if (!(dest = ft_strsplit(env->input, ";")))
		return (NULL);
	while (dest[i])
	{
		if (!(tmp = ft_strtrim(dest[i])))
			return (NULL);
		if (ft_strcmp(tmp, dest[i]) != 0)
		{
			free(dest[i]);
			dest[i] = tmp;
		}
		i++;
	}
	return (dest);
}

int					parser(t_env *env)
{
	unsigned int	i;
	bool			err;
	int				ret;

	i = 0;
	err = false;
	if (!env->input || env->input[0] == '\0')
		return (0);
	if (!(env->semisplit = make_semisplit(env)))
		return (-1);
	while (env->semisplit[i])
	{
		ret = parse_cmd(env, env->semisplit[i]);
		if (ret == -1 && !(env->semisplit = free_ctab(env->semisplit)))
			return (-1);
		else if (ret == 1)
			err = true;
		i++;
	}
	env->semisplit = free_ctab(env->semisplit);
	return (err ? 1 : 0);
}
