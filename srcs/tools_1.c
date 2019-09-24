/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:38:13 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/24 10:41:53 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

uint32_t	maj(uint32_t x, uint32_t y, uint32_t z)
{
	return (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)));
}

uint32_t	ep0(uint32_t x)
{
	return (rightrotate(x, 2) ^ rightrotate(x, 13) ^ rightrotate(x, 22));
}

uint32_t	ep1(uint32_t x)
{
	return (rightrotate(x, 6) ^ rightrotate(x, 11) ^ rightrotate(x, 25));
}

uint32_t	sig0(uint32_t x)
{
	return (rightrotate(x, 7) ^ rightrotate(x, 18) ^ ((x) >> 3));
}

uint32_t	sig1(uint32_t x)
{
	return (rightrotate(x, 17) ^ rightrotate(x, 19) ^ ((x) >> 10));
}
