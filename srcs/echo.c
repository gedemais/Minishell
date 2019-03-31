# include "../includes/minishell.h"

static bool	ft_get_opt(char **input, int *i)
{
	while (input[*i][0] == '-')
	{
		if (input[*i][1] == '\0')
			return (false);
		else if (input[*i][1] == 'n' && input[*i][2] == '\0')
		{
			*i = *i + 1;
			return (true);
		}
		*i = *i + 1;
	}
	return (false);
}

int			ft_echo(char **input)
{
	int		i;
	bool	n;

	i = 1;
	n = false;
	if (ft_strcmp(input[0], "echo") != 0)
		return (1);
	n = ft_get_opt(input, &i);
	while (input[i])
	{
		ft_putstr(input[i]);
		if (input[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	if (n == true)
		ft_putchar('%');
	ft_putchar('\n');
	return (0);
}
