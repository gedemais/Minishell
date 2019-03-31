#include "../includes/minishell.h"
/*
static int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}*/

static void	ft_tabdel(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	ft_strdel(&tab[i]);
	free(tab);
}

int		ft_exec(char **env, char *input)
{
	char	**semicols;
	char	**split;
	int	i;

	i = 0;
	(void)env;
	if (!(semicols = ft_strsplit(input, ';')))
		return (-1);
	while (semicols[i])
	{
		if (!(split = ft_strsplit(semicols[i], ' ')))
			return (-1);
		ft_lexer(split, env);
		ft_tabdel(split);
		i++;
	}
	ft_tabdel(semicols);
	ft_strdel(&input);
	return (0);
}
