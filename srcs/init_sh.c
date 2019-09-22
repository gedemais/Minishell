/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:00:55 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 18:24:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst				*t_env_lstnew(char *var)
{
	t_env_lst		*new;
	unsigned int	i;

	i = 0;
	if (!var || !var[0])
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (NULL);
	if (!(new = (t_env_lst*)malloc(sizeof(t_env_lst)))
		|| !(new->name = ft_strndup(var, (int)i))
		|| !(new->val = ft_strdup(&var[i + 1])))
		return (NULL);
	new->next = NULL;
	return (new);
}

int						t_env_lst_pushfront(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*tmp;

	if (!*lst)
		return (1);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (0);
}

static inline t_env_lst	*init_env_lst(char **env_t)
{
	t_env_lst		*lst;
	unsigned int	i;

	i = 1;
	if (!env_t)
		return (NULL);
	if (!(lst = t_env_lstnew(env_t[0])))
		return (NULL);
	while (env_t[i])
	{
		if (t_env_lst_pushfront(&lst, t_env_lstnew(env_t[i])) != 0)
			return (NULL);
		i++;
	}
	return (lst);
}

static inline int		shlvl(t_env_lst *env)
{
	t_env_lst	*shlvl;
	int			value;

	if (!env || !(shlvl = get_var(env, "SHLVL")))
		return (1);
	value = (int)ft_atoi(shlvl->val);
	free(shlvl->val);
	if (!(shlvl->val = ft_itoa(value + 1)))
		return (-1);
	return (0);
}

int						init_sh(t_env *env, char **environment)
{
	env->env = init_env_lst(environment);
	if (!(env->env = build_env(env)))
		return (-1);
	if (shlvl(env->env) == -1)
		return (-1);
	env->environment = NULL;
	if (!(env->environment = refresh_env(env->env, env->environment)))
		return (-1);
	return (0);
}
