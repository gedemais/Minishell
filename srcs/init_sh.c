#include "minishell.h"

static inline t_env_lst	*t_env_lstnew(char *var)
{
	t_env_lst	*new;
	unsigned int	i;

	i = 0;
	if (!var || !var[0])
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (NULL);
	if (!(new = (t_env_lst*)malloc(sizeof(t_env_lst)))
		|| !(new->name = ft_strndup(var, (int)i))
		|| !(new->val = ft_strdup(&var[i + 1])))
		return (NULL);
	new->next = NULL;
	return (new);
}

static inline int		t_env_lst_pushfront(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*tmp;

	if (!*lst)
		return (1);
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	new->next = NULL;
	tmp->next = new;
	return (0);
}


static inline t_env_lst	*init_env_lst(char **env_t)
{
	t_env_lst	*lst;
	unsigned int	i;

	i = 1;
	if (!(lst = t_env_lstnew(env_t[0])))
		return (NULL);
	while (env_t[i])
	{
		if (t_env_lst_pushfront(&lst, t_env_lstnew(env_t[i])) != 0)
			return (NULL);
		i++;
	}
	return (lst);
}

int			init_sh(t_env *env, char **environment)
{
	if (!(env->env = init_env_lst(environment)))
		return (-1);
	return (0);
}
