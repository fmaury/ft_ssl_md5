/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 10:30:21 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/24 10:40:50 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static const unsigned int g_o[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

void	sha256_init(t_ctx *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void	handle_sha256_transform(t_ctx *ctx, unsigned int t[2],
		unsigned int m[64], unsigned int h[8])
{
	int	i;

	i = 0;
	while (i < 64)
	{
		t[0] = h[7] + ep1(h[4]) + ch(h[4], h[5], h[6]) + g_o[i] + m[i];
		t[1] = ep0(h[0]) + maj(h[0], h[1], h[2]);
		h[7] = h[6];
		h[6] = h[5];
		h[5] = h[4];
		h[4] = h[3] + t[0];
		h[3] = h[2];
		h[2] = h[1];
		h[1] = h[0];
		h[0] = t[0] + t[1];
		i++;
	}
	ctx->state[0] += h[0];
	ctx->state[1] += h[1];
	ctx->state[2] += h[2];
	ctx->state[3] += h[3];
	ctx->state[4] += h[4];
	ctx->state[5] += h[5];
	ctx->state[6] += h[6];
	ctx->state[7] += h[7];
}

void	set_transform_value(t_ctx *ctx, unsigned int h[8])
{
	h[0] = ctx->state[0];
	h[1] = ctx->state[1];
	h[2] = ctx->state[2];
	h[3] = ctx->state[3];
	h[4] = ctx->state[4];
	h[5] = ctx->state[5];
	h[6] = ctx->state[6];
	h[7] = ctx->state[7];
}

void	sha256_transform(t_ctx *ctx, const unsigned char data[])
{
	unsigned int	h[8];
	unsigned int	i;
	unsigned int	j;
	unsigned int	t[2];
	unsigned int	m[64];

	i = 0;
	j = 0;
	while (i < 16)
	{
		m[i] = (data[j] << 24) | (data[j + 1] << 16) |
		(data[j + 2] << 8) | (data[j + 3]);
		i++;
		j += 4;
	}
	while (i < 64)
	{
		m[i] = sig1(m[i - 2]) + m[i - 7] + sig0(m[i - 15]) + m[i - 16];
		i++;
	}
	set_transform_value(ctx, h);
	handle_sha256_transform(ctx, t, m, h);
}
