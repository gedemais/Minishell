#include "../includes/minishell.h"

char	*ft_strndup(char *str, int len)
{
	char	*new;
	int	i;

	i = 0;
	while (str[i] && i < len)
		i++;
	if (!(new = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_get_var_name(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (ft_strndup(var, i));
}

char	*ft_get_var_value(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	i++;
	return (ft_strdup(&var[i]));
}

t_envi	*ft_ms_lstnew(char *var)
{
	t_envi	*new;

	if (!(new = (t_envi*)malloc(sizeof(t_envi))))
		return (NULL);
	if (!(new->name = ft_get_var_name(var)))
		return (NULL);
	if (!(new->value = ft_get_var_value(var)))
		return (NULL);
	return (new);
}

int	ft_ms_lst_pushfront(t_envi **lst, t_envi *new)
{
	t_envi	*tmp;

	if (!new || !*lst)
		return (-1);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
}

t_envi	*ft_make_env(char **environ)
{
	t_envi	*lst;
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (i == 0)
		{
			if (!(lst = ft_ms_lstnew(environ[i])))
				return (NULL);
		}
		else if (ft_ms_lst_pushfront(&lst, ft_ms_lstnew(environ[i])) == -1)
				return (NULL);
		i++;
	}
	return (lst);
}
