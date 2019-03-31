#include "../includes/minishell.h"


int		ft_builtins(char **input, char **env)
{
	int		ret;

	ret = 0;
	(void)env;
	if (ft_strcmp(input[0], "exit") == 0)
		exit (EXIT_SUCCESS);
	else if (ft_strcmp(input[0], "echo") == 0)
		ret = ft_echo(input);
/*	else if (ft_strcmp(input[0], "env") == 0)
		ret = ft_env(input);
	else if (ft_strcmp(input[0], "setenv") == 0)
		ret = ft_setenv(input);
	else if (ft_strcmp(input[0], "unsetenv") == 0)
		ret = ft_unsetenv(input);
	else if (ft_strcmp(input[0], "cd") == 0)
		ret = ft_cd(input);*/
	else
		return (1);
	return (ret);
}

