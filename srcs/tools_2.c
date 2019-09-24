/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:41:38 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/24 10:41:47 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

uint32_t	leftrotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

uint32_t	rightrotate(uint32_t x, uint32_t c)
{
	return ((x >> c) | (x << (32 - c)));
}

uint32_t	ch(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) ^ (~(x) & (z)));
}
