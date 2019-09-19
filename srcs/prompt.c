#include "minishell.h"

static inline t_env_lst	*get_var(t_env_lst *env, char *name)
{
	t_env_lst		*tmp;
	unsigned int	i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static inline char		*make_path(t_env_lst *path)
{
	unsigned int	i;

	i = 0;
	if (!path)
		return ("\0");
	while (path->val[i])
		i++;
	while (path->val[i] != '/' && i > 0)
		i--;
	return (&path->val[i + 1]);
}

int						prompt(t_env *env, int state)
{
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('$');
	ft_putchar('{');
	ft_putstr(STOP);
	ft_putstr(make_path(get_var(env->env, "PWD")));
	ft_putstr(state == 0 ? L_GREEN : L_RED);
	ft_putchar('}');
	ft_putstr(STOP);
	ft_putstr(GRA);
	ft_putstr("-> ");
	ft_putstr(STOP);
	return (0);
}
