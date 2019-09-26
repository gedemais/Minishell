/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:48 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 16:15:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		del_node(t_env_lst *node)
{
	free(node->name);
	free(node->val);
	free(node);
	return (0);
}

char	**free_ctab(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

int		free_environment(t_env_lst *env)
{
	if (env->next)
		free_environment(env->next);
	free(env->name);
	free(env->val);
	free(env);
	env = NULL;
	return (0);
}

int		free_env(t_env *env)
{
	if (env->input)
		free(env->input);
	if (env->env)
	{
		free_environment(env->env);
		env->env = NULL;
	}
	if (env->semisplit)
		env->semisplit = free_ctab(env->semisplit);
	if (env->split)
		env->split = free_ctab(env->split);
	if (env->environment)
		env->environment = free_ctab(env->environment);
	return (0);
}
