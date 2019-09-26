/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:06 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 00:59:46 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline char	**make_split(char *cmd)
{
	char		**dest;
	char		*tmp;
	unsigned int	i;

	i = 0;
	if (!(tmp = ft_strtrim(cmd)))
		return (NULL);
	if (!(dest = ft_strsplit(tmp, " \t")))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (dest);
}

static inline int	parse_cmd(t_env *env, char *cmd)
{
	int	ret;

	if (!(env->split = make_split(cmd))
		|| !(env->split = expansions(env, env->split)))
		return (-1);
	ret = builtins(env);
	if ((ret == -1 || ret == 1) && !(env->split = free_ctab(env->split)))
		return (ret == -1 ? -1 : 0);
	else if (ret == 2 && !(env->split = free_ctab(env->split)))
		return (1);
	ret = exec_binary(env);
	if (ret == 1)
		return (ret);
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

int					parser(t_env *env)
{
	unsigned int	i;
	bool			err;
	int				ret;

	i = 0;
	err = false;
	if (!env->input || env->input[0] == '\0')
		return (0);
	if (!(env->semisplit = ft_strsplit(env->input, ";")))
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
