#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK "\033[22;30m"
# define BLUE "\033[22;34m"
# define RED "\033[22;31m"
# define L_RED "\033[01;31m"
# define L_GREEN "\033[01;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"



# include "../libft/libft.h"
#include <stdio.h>

int	ft_find_var(char **env, char *var);
char	**ft_cpy_env(char **environ);
void	ft_prompt(char **env, int mode);
int	ft_exec(char **env, char *input);
int	ft_lexer(char **input, char **env);
char	*ft_binarys(char *cmd, char **env);

#endif
