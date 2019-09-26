/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:20 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 13:15:15 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	ft_exit(t_env *env, char **av)
{
	(void)av;
	free_env(env);
	exit(EXIT_SUCCESS);
}

int					ft_env(t_env *env, char **av)
{
	t_env_lst	*tmp;

	(void)av;
	tmp = env->env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putchar('=');
		ft_putendl(tmp->val);
		tmp = tmp->next;
	}
	return (0);
}

int					builtins(t_env *env)
{
	static char		*b_names[NB_BUILTINS] = {"env", "setenv", "unsetenv",
					"exit", "echo", "cd"};
	static int		(*b_func[NB_BUILTINS])(t_env*, char**) = {ft_env, ft_setenv,
					ft_unsetenv, ft_exit, ft_echo, ft_cd};
	unsigned int	i;
	int				ret;

	i = 0;
	if (!env->split || !env->split[0])
		return (1);
	while (i < NB_BUILTINS)
	{
		if (ft_strcmp(b_names[i], env->split[0]) == 0)
		{
			ret = b_func[i](env, env->split);
			if (ret == -1)
				return (-1);
			return (ret == 0 ? 1 : 2);
		}
		i++;
	}
	return (0);
}
