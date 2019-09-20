/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 12:51:50 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/20 10:56:30 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

char	*ft_strndup(char *s1, int size)
{
	char	*dest;
	int	i;

	i = 0;
	if (!s1 || size > (int)ft_strlen(s1))
		return (NULL);
	if (!(dest = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (s1[i] && i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
