#include "../includes/minishell.h"

char	*ft_make_var(char *name, char *val)
{
	char	*dest;
	int	len;

	len = ft_strlen(name) + ft_strlen(val) + 1;
	if (!(dest = ft_strnew(len)))
		return (NULL);
	dest = ft_strcat(dest, name);
	dest = ft_strcat(dest, "=");
	dest = ft_strcat(dest, val);
	return (dest);
}

t_env	*ft_unsetenv(t_env *env, char **split)
{
	t_envi	*tmp;
	t_envi	*tmp2;

	tmp = env->env;
	tmp2 = env->env->next;
	if (!split[1] || split[2])
	{
		ft_putstr_fd("unsetenv : wrong args\n", 2);
		return (env);
	}
	while (tmp2)
	{
		if (ft_strcmp(tmp2->name, split[1]) == 0)
		{
			tmp->next = tmp2->next;
			free(tmp2->name);
			free(tmp2->value);
			free(tmp2);
			return (env);
		}
		tmp = tmp->next;
		tmp2 = tmp2->next;
	}
	ft_putstr_fd("unsetenv : ", 2);
	ft_putstr_fd(split[1], 2);
	ft_putstr_fd(" : no such variable in env\n", 2);
	return (env);
}

t_env	*ft_setenv(t_env *env, char **split)
{
	char	*var;

	if (!split[1] || !split[2] || split[3])
	{
		ft_putstr_fd("setenv : wrong args\n", 2);
		return (env);
	}
	if (!(var = ft_make_var(split[1], split[2])))
		return (NULL);
	if (ft_ms_lst_pushfront(&(env->env), ft_ms_lstnew(var)) == -1)
		return (env);
	ft_strdel(&var);
	return (env);
}

char	*ft_get_var_val(t_env *env, char *var)
{
	t_envi	*tmp;
	int	len;

	len = ft_strlen(var);
	tmp = env->env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, var, len) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_env(t_envi *env)
{
	t_envi	*tmp;

	if (env == NULL)
		return (-1);
	tmp = env;
	while (tmp)
	{
		ft_putstr(tmp->name);
		ft_putchar('=');
		ft_putendl(tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
