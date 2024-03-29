/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlf1join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:20:00 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/04 14:54:39 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strlf1join(char *s1, char *s2, int len1, int len2)
{
	int		j;
	char	*str;

	j = 0;
	if (!(str = ft_strnew(len1 + len2)))
		return (NULL);
	if (s1 != NULL)
	{
		str = ft_memcpy(str, s1, len1);
		free(s1);
	}
	if (s2 != NULL)
	{
		while (j < len2)
		{
			str[len1 + j] = s2[j];
			j++;
		}
	}
	return (str);
}
