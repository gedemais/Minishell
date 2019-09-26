/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 11:28:43 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 18:18:17 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					replace_value(t_env_lst *env, char *name, char *val)
{
	t_env_lst	*tmp;
	char		*var;
	bool		found;

	tmp = env;
	found = false;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			free(tmp->val);
			if (!(tmp->val = ft_strdup(val)))
				return (-1);
			found = true;
		}
		tmp = tmp->next;
	}
	if (!found)
	{
		if (!(var = re_assemble(name, "=", val))
			|| t_env_lst_pushfront(&env, t_env_lstnew(var)) != 0)
			return (-1);
		free(var);
	}
	return (0);
}

static inline int	setenv_cases(t_env *env, char **av)
{
	unsigned int	len;

	(void)env;
	len = 0;
	while (av[len])
		len++;
	if (len == 2)
	{
		ft_putstr_fd("setenv: required value for variable: ", 2);
		ft_putendl_fd(av[1], 2);
		return (1);
	}
	if (len > 3)
	{
		ft_putendl_fd("setenv: Too many arguments", 2);
		return (1);
	}
	return (0);
}

int					ft_setenv(t_env *env, char **av)
{
	char	*var;
	int		ret;
	int		i;

	i = -1;
	if (!av[1])
		return (ft_env(env, av));
	ret = setenv_cases(env, av);
	if (ret == -1 || ret == 1)
		return (ret);
	if (get_var(env->env, av[1]) && replace_value(env->env, av[1], av[2]) == 0)
		return (0);
	while (av[1][++i])
		if (av[1][i] == '=')
		{
			ft_putstr_fd(SETENV_ERR_0, 2);
			return (1);
		}
	if (!(var = re_assemble(av[1], "=", av[2])))
		return (-1);
	if ((env->env && t_env_lst_pushfront(&env->env, t_env_lstnew(var)) != 0)
		|| (!env->env && !(env->env = t_env_lstnew(var))))
		return (-1);
	free(var);
	return (0);
}
