#include "../includes/minishell.h"

int	ft_lexer(char **input, char **env)
{
	char	*cmd_path;
	int	i;

	i = 0;
	while (input[i])
	{
		if ((cmd_path = ft_binarys(input[i], env)))
			execve(cmd_path, &input[i], env);
		i++;
	}
	return (0);
}
