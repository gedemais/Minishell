/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:11 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 18:18:34 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst				*get_var(t_env_lst *env, char *name)
{
	t_env_lst		*tmp;
	unsigned int	i;

	i = 0;
	if (!env || !name || !name[0])
		return (NULL);
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static inline char		*make_path(t_env_lst *path, t_env_lst *home)
{
	unsigned int		i;

	i = 0;
	if (!path)
		return ("\0");
	if (home && ft_strcmp(path->val, home->val) == 0)
		return ("~");
	if (path->val[0] == '/' && !path->val[1])
		return ("/");
	while (path->val[i])
		i++;
	while (path->val[i] != '/' && i > 0)
		i--;
	return (&path->val[i + 1]);
}

int						prompt(t_env *env, int state)
{
	static t_env_lst	*home = NULL;

	if (!home && !(home = get_var(env->env, "HOME")))
		(void)state;
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('$');
	ft_putchar('{');
	ft_putstr(STOP);
	ft_putstr(make_path(get_var(env->env, "PWD"), home));
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
	return (0);
}
