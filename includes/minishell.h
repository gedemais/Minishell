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

# define PUT ft_putstr("There\n");
# define PUT1 ft_putstr("There1\n");
# define PUT2 ft_putstr("There2\n");
# define PUT3 ft_putstr("There3\n");
# define PUT4 ft_putstr("There4\n");
# define PUT5 ft_putstr("There5\n");
# define PUT6 ft_putstr("There6\n");
# define PUT7 ft_putstr("There7\n");
# define PUT8 ft_putstr("There8\n");

typedef struct		s_envi
{
	char		*name;
	char		*value;
	struct s_envi	*next;
}			t_envi;

typedef struct	s_env
{
	t_envi	*env;
	char	*input;
	char	**semisplit;
	char	**split;
	int	mode;
}		t_env;

t_envi		*ft_ms_lstnew(char *var);
int		ft_ms_lst_pushfront(t_envi **lst, t_envi *new);
t_envi		*ft_make_env(char **environ);

void		ft_prompt(t_env *env, int mode);

int		ft_parser(t_env *env);

int		ft_builtins_tree(t_env *env);

void		ft_free_env(t_envi *env);

t_env		*ft_unsetenv(t_env *env, char **split);
t_env		*ft_setenv(t_env *env, char **split);
int		ft_env(t_envi *env);
char		*ft_get_var_val(t_env *env, char *var);
void		ft_free_splits(char **split);

int		ft_binarys(t_env *env, char *cmd, char **params);
#endif
