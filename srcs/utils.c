/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 18:01:22 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/22 18:26:50 by gedemais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	env_len(t_env_lst *env)
{
	t_env_lst		*tmp;
	unsigned int	ret;

	tmp = env;
	ret = 0;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

char			*re_assemble(char *s1, char *s2, char *s3)
{
	char	*dest;
	char	*tmp;

	if (!(tmp = ft_strjoin(s1, s2)))
		return (NULL);
	if (!(dest = ft_strjoin(tmp, s3)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (dest);
}

char			*ft_strduptil(char *str, char stop)
{
	char			*dest;
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	if (!(dest = ft_strnew(i)))
		return (NULL);
	dest = ft_strncpy(dest, str, i);
	return (dest);
}

char			*trim_path_end(char *path)
{
	unsigned int	i;

	i = (unsigned int)ft_strlen(path) - 1;
	while (i > 0 && path[i] != '/')
		i--;
	while (path[i])
	{
		path[i] = '\0';
		i++;
	}
	return (path);
}

bool			is_dots(char **av)
{
	unsigned int	i;

	i = 0;
	while (av[1][i])
	{
		if (av[1][i] != '.')
			return (false);
		i++;
	}
	return (true);
}
