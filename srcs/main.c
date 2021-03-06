/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:01 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/25 15:03:20 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline int	minishell(char **environment)
{
	t_env	env;
	int		state;

	ft_memset(&env, 0, sizeof(t_env));
	if (init_sh(&env, environment) != 0)
		return (-1);
	state = 0;
	prompt(&env, state);
	while (get_next_line(0, &(env.input)))
	{
		state = parser(&env);
		ft_strdel(&(env.input));
		prompt(&env, state);
	}
	free_env(&env);
	return (0);
}

int					main(int argc, char **argv, char **env)
{
	(void)argv;
	if (argc > 2)
	{
		ft_putstr_fd("No args available\n", 2);
		return (1);
	}
	if (minishell(env) != 0)
		return (1);
	return (0);
}
