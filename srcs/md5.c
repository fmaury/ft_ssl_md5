/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 11:44:59 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/25 13:14:00 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static uint32_t	g_r[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17,
	22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

static int		g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

void			handle_value(int i, uint32_t l[])
{
	if (i < 16)
	{
		l[4] = (l[1] & l[2]) | ((~l[1]) & l[3]);
		l[5] = i;
	}
	else if (i < 32)
	{
		l[4] = (l[3] & l[1]) | ((~l[3]) & l[2]);
		l[5] = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		l[4] = l[1] ^ l[2] ^ l[3];
		l[5] = (3 * i + 5) % 16;
	}
	else
	{
		l[4] = l[2] ^ (l[1] | (~l[3]));
		l[5] = (7 * i) % 16;
	}
}

void			switch_value(uint32_t l[], int i, uint32_t *w)
{
	uint32_t	temp;

	temp = l[3];
	l[3] = l[2];
	l[2] = l[1];
	l[1] = l[1] + leftrotate((l[0] + l[4] + g_k[i] + w[l[5]]), g_r[i]);
	l[0] = temp;
}

void			init_l(uint32_t l[], uint32_t *h)
{
	l[0] = h[0];
	l[1] = h[1];
	l[2] = h[2];
	l[3] = h[3];
}

uint32_t		*handle_md5(uint32_t l[], uint64_t new_len, uint8_t *msg,
				uint32_t *h)
{
	size_t		i;
	uint64_t	offset;
	uint32_t	*w;

	offset = 0;
	while (offset < new_len)
	{
		w = (uint32_t *)(msg + offset);
		init_l(l, h);
		i = 0;
		while (i < 64)
		{
			handle_value(i, l);
			switch_value(l, i, w);
			i++;
		}
		h[0] += l[0];
		h[1] += l[1];
		h[2] += l[2];
		h[3] += l[3];
		offset += (512 / 8);
	}
	return (h);
}

int				md5(t_ssl *ssl)
{
	uint8_t		*msg;
	uint64_t	new_len;
	uint32_t	bits_len;
	uint32_t	l[6];
	uint32_t	*h;

	if (!(h = (uint32_t*)ft_memalloc(4 * sizeof(uint32_t))))
		return (err(MALLOC, ""));
	h[0] = 0x67452301;
	h[1] = 0xEFCDAB89;
	h[2] = 0x98BADCFE;
	h[3] = 0x10325476;
	new_len = ((((ssl->size + 8) / 64) + 1) * 64) - 8;
	if (!(msg = ft_memalloc(new_len + 64)))
		return (err(MALLOC, ""));
	ft_memcpy(msg, ssl->plain, ssl->size);
	msg[ssl->size] = 128;
	bits_len = 8 * ssl->size;
	ft_memcpy(msg + new_len, &bits_len, 4);
	ssl->hash = (unsigned char*)handle_md5(l, new_len, msg, h);
	free(msg);
	return (1);
}
