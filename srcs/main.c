#include "minishell.h"

static inline int	minishell(char **environment)
{
	t_env	env;
	int	state;

	state = 0; // everything FINE
	if (init_sh(&env, environment) != 0)
		return (-1);
	prompt(&env, state);
	while (get_next_line(0, &(env.input)))
	{
		state = parser(&env, env.input);
		ft_strdel(&(env.input));
		prompt(&env, state);
		env.input = NULL;
		if (state == -1)
		{
		//	free_env(env);
			return (1);
		}
	}
	return (0);
}

int			main(int argc, char **argv, char **env)
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
