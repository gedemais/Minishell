#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK "\033[22;30m"
# define BLUE "\033[22;34m"
# define RED "\033[22;31m"
# define L_RED "\033[01;31m"
# define L_GREEN "\033[01;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct	s_env
{
	char	**env;
	char	*input;
	char	**semisplit;
	char	**split;
}		t_env;

# define PUT ft_putstr("There\n");
# define PUT1 ft_putstr("There1\n");
# define PUT2 ft_putstr("There2\n");
# define PUT3 ft_putstr("There3\n");
# define PUT4 ft_putstr("There4\n");
# define PUT5 ft_putstr("There5\n");
# define PUT6 ft_putstr("There6\n");
# define PUT7 ft_putstr("There7\n");
# define PUT8 ft_putstr("There8\n");

int		prompt(t_env *env, int state);
int		init_sh(t_env *env, char **environment);
int		parser(t_env *env, char *line);
int		builtins(t_env *env);
#endif
