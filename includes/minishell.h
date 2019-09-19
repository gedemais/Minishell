#ifndef MINISHELL_H
# define MINISHELL_H

# define BLACK "\033[22;30m"
# define BLUE "\033[22;34m"
# define RED "\033[22;31m"
# define L_RED "\033[01;31m"
# define L_GREEN "\033[01;32m"
# define GRA "\033[1m"
# define STOP "\033[0m"

# define NB_BUILTINS 6

# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>

typedef struct		s_env_lst t_env_lst;

struct			s_env_lst
{
	char		*name;
	char		*val;
	t_env_lst	*next;
};

typedef struct		s_env
{
	t_env_lst	*env;
	char		*input;
	char		**semisplit;
	char		**split;
	char		**environment;
}			t_env;



int			prompt(t_env *env, int state);
int			init_sh(t_env *env, char **environment);
int			parser(t_env *env);


int			builtins(t_env *env);
t_env_lst		*get_var(t_env_lst *env, char *name);
int			exec_binary(t_env *env);
char			*re_assemble(char *s1, char *s2, char *s3);
unsigned int		env_len(t_env_lst *env);
char			**refresh_env(t_env_lst *env, char **environment);

/*
** Free
*/
int			free_ctab(char **tab);
#endif
