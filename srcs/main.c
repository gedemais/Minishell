/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 17:51:04 by gedemais          #+#    #+#             */
/*   Updated: 2019/05/12 17:52:32 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		ft_minishell(char **environ)
{
	t_env	env;

	env.mode = 0;
	if (!(env.env = ft_cpy_env(environ)))
		return (-1);
	ft_prompt(env.env, env.mode);
	while (get_next_line(0, &(env.input)) >= 0)
	{
		if ((env.mode = ft_parser(&env)) == -1)
			return (-1);
		ft_prompt(env.env, env.mode);
		ft_strdel(&(env.input));
	}
	return (0);
}

int		main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc == 1)
	{
		if (ft_minishell(env) == -1)
			return (1);
	}
	else
		ft_putstr_fd("Usage : ./minishell\n", 2);
	return (0);
}
