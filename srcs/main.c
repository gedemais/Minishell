#include "../includes/minishell.h"

int	ft_minishell(char **environ)
{
	char	**env;
	char	*input;
	int	mode;

	mode = 0;
	if (!(input = ft_strnew(1024)))
		return (-1);
	if (!(env = ft_cpy_env(environ)))
		return (-1);
	ft_prompt(env, mode);
	while (read(0, input, 1024) >= 0)
	{
		if (input[0] != '\n' && (mode = ft_exec(env, ft_strsplit(input, '\n')[0])) == -1)
			return (-1);
		ft_prompt(env, mode);
		ft_bzero(input, 1024);
//		ft_strdel(&input); Pr GNL
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
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
