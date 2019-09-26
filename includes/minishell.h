/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 19:49:24 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/26 16:20:30 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define MAX_ARG 4096

# define SETENV_ERR_0 "setenv: variable name must not contain = character.\n"

# define CD_ERR_EACCES "cd: permission denied: "
# define CD_ERR_ENOENT "cd: no such file or directory: "
# define CD_ERR_TMARGS "cd: Too many args\n"

# define B_PATH "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <limits.h>
# include <pwd.h>

typedef struct s_env_lst	t_env_lst;

struct						s_env_lst
{
	char					*name;
	char					*val;
	t_env_lst				*next;
};

typedef struct				s_env
{
	t_env_lst				*env;
	char					*input;
	char					**semisplit;
	char					**split;
	char					**environment;
}							t_env;

int							prompt(t_env *env, int state);
int							init_sh(t_env *env, char **environment);
int							parser(t_env *env);
int							builtins(t_env *env);
t_env_lst					*get_var(t_env_lst *env, char *name);
int							exec_binary(t_env *env);
char						*re_assemble(char *s1, char *s2, char *s3);
unsigned int				env_len(t_env_lst *env);
char						**refresh_env(t_env_lst *env, char **environment);
int							ft_env(t_env *env, char **av);
int							ft_unsetenv(t_env *env, char **av);
int							ft_setenv(t_env *env, char **av);
int							ft_cd(t_env *env, char **av);
int							ft_echo(t_env *env, char **av);
t_env_lst					*t_env_lstnew(char *var);
int							t_env_lst_pushfront(t_env_lst **l, t_env_lst *new);
int							replace_value(t_env_lst *env, char *name, char *v);
char						**expansions(t_env *env, char **split);
char						*trim_path_end(char *path);
char						*ft_strduptil(char *str, char stop);
t_env_lst					*build_env(t_env *env);
bool						is_dots(char **av);
t_env_lst					*get_pwd(void);
int							secure_pwd(t_env *env);
char						*cd_less(t_env *env);
char						*cd_home(t_env *env, int *status);
bool						check_white(char **av);
int							replace_paths(t_env *env, t_env_lst *pwd, char *path);

/*
** Free
*/
char						**free_ctab(char **tab);
int							free_environment(t_env_lst *env);
int							free_env(t_env *env);
int							del_node(t_env_lst *node);
#endif
