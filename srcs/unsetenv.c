/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 18:15:54 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 18:40:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	unsetenv_cases(t_env_lst **env, char **av)
{
	t_env_lst	*tmp;
	t_env_lst	*tmp2;

	tmp = (*env);
	tmp2 = (*env)->next;
	if (!av[1] || !av[1][0])
		return (1);
	if (ft_strcmp(tmp->name, av[1]) == 0)
	{
		del_node(*env);
		(*env) = tmp2;
		return (1);
	}
	while (tmp2->next)
	{
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if (ft_strcmp(tmp2->name, av[1]) == 0)
	{
		del_node(tmp2);
		tmp->next = NULL;
		return (1);
	}
	return (0);
}

static inline int			unsetenv_loop(t_env *env, char **av, bool *not_found)
{
	t_env_lst		*tmp;
	t_env_lst		*tmp2;
	unsigned int	i;

	i = 0;
	while (env->env && av[++i])
	{
		tmp = env->env;
		tmp2 = env->env->next;
		while (tmp2)
			if (ft_strcmp(tmp2->name, av[i]) == 0)
			{
				*not_found = false;
				tmp2 = tmp2->next;
				del_node(tmp);
				tmp->next = tmp2;
			}
			else
			{
				tmp = tmp->next;
				tmp2 = tmp2->next;
			}
	}
	return (0);
}

int					ft_unsetenv(t_env *env, char **av)
{
	bool			not_found;
	int				i;

	i = -1;
	not_found = false;
	if (!env->env)
		return (1);
	while (env->env && av[++i])
		unsetenv_cases(&env->env, &av[i]);
	i = 0;
	if (unsetenv_loop(env, av, &not_found) != 0)
		return (1);
	return (not_found ? 1 : 0);
}

