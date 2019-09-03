/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 09:38:54 by fmaury            #+#    #+#             */
/*   Updated: 2019/05/06 13:16:35 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while (tmp1 && tmp2 && tmp1[i] && tmp2[i] && i < n)
	{
		if (tmp1[i] - tmp2[i] == 0)
			i++;
		else
			return (tmp1[i] - tmp2[i]);
	}
	if (i < n)
	{
		if (tmp1 && ft_strlen((char*)tmp1) > ft_strlen((char*)tmp2))
			return (tmp1[i]);
		else if (tmp2)
			return (tmp2[i]);
	}
	return (0);
}
