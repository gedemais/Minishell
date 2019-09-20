/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gedemais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 17:26:35 by gedemais          #+#    #+#             */
/*   Updated: 2019/09/20 11:29:06 by demaisonc        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;

	if (!s1)
		return ((char*)s2);
	if (!s2)
		return ((char*)s1);
	if (!(dest = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	dest[0] = '\0';
	dest = ft_strcat(dest, s1);
	dest = ft_strcat(dest, s2);
	return (dest);
}
