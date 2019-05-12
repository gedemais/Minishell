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
# include <stdbool.h>

# define PUT ft_putstr("There\n");
# define PUT1 ft_putstr("There1\n");
# define PUT2 ft_putstr("There2\n");
# define PUT3 ft_putstr("There3\n");
# define PUT4 ft_putstr("There4\n");
# define PUT5 ft_putstr("There5\n");
# define PUT6 ft_putstr("There6\n");
# define PUT7 ft_putstr("There7\n");
# define PUT8 ft_putstr("There8\n");

typedef struct	s_env
{
	char	**env;
	char	*input;
	int	mode;
}		t_env;

int		ft_find_var(char **env, char *var);
char	**ft_cpy_env(char **environ);
void	ft_prompt(char **env, int mode);
int		ft_exec(char **env, char *input);
int		ft_lexer(char **input, char **env);
char	*ft_binarys(char *cmd, char **env);
int		ft_echo(char **input);
int		ft_builtins(char **input, char **env);


int		ft_parser(t_env *env);

int		ft_builtins_tree(t_env *env);

t_env		*ft_free_env(t_env *env);


#endif
