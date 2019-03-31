#include "../includes/minishell.h"

pid_t	ft_create_process(void)
{
	pid_t	pid;

	pid = fork();
	while (pid == -1 && errno == EAGAIN)
	{
		perror("fork");
		pid = fork();
	}
	if (pid == -1)
	{	
		kill(pid, SIGKILL);
		pid = 0;
	}
	return (pid);
}

int		ft_launch_cmd(char *cmd_path, char **input, char **env, int i)
{
	pid_t	pid;

	if ((pid = ft_create_process()) == -1)
		return (-1);
	else if (pid == 0)
		execve(cmd_path, &input[i], env);
	else if (pid > 0)
		return (pid);
	return (0);
}

int		ft_lexer(char **input, char **env)
{
	char	*cmd_path;
	int		status;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	while (input[i])
	{
		if ((ret = ft_builtins(input, env)) < 0)
			return (-1);
		else if (ret == 0)
			break ;
		else if ((cmd_path = ft_binarys(input[i], env)))
		{
			if (ft_launch_cmd(cmd_path, input, env, i) == -1)
				return (-1);
			waitpid(-1, &status, 0);
		}
		else
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putstr_fd(input[i], 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
		i++;
	}
	return (0);
}
