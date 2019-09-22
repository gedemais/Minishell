/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:16 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 19:43:32 by gedemais         ###   ########.fr       */
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
		(*env) = tmp2;
		free(tmp);
		return (1);
	}
	while (tmp2->next)
	{
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	if (ft_strcmp(tmp2->name, av[1]) == 0)
	{
		free(tmp2);
		tmp->next = NULL;
		return (1);
	}
	return (0);
}

int					ft_unsetenv(t_env *env, char **av)
{
	t_env_lst		*tmp;
	t_env_lst		*tmp2;
	unsigned int	i;

	i = 0;
	if (unsetenv_cases(&env->env, av))
		return (0);
	while (av[++i])
	{
		tmp = env->env;
		tmp2 = env->env->next;
		while (tmp2)
		{
			if (ft_strcmp(tmp2->name, av[i]) == 0)
			{
				tmp2 = tmp2->next;
				free(tmp->next);
				tmp->next = tmp2;
				return (0);
			}
			tmp = tmp->next;
			tmp2 = tmp2->next;
		}
	}
	return (1);
}

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
	if (t_env_lst_pushfront(&env->env, t_env_lstnew(var)) != 0)
		return (-1);
	free(var);
	return (0);
}
