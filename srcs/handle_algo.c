/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:57:59 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/25 12:22:33 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static t_algo		g_algo[] = {
	{"md5", md5, "MD5", 16},
	{"sha256", sha256, "SHA256", 32},
	{NULL, NULL, NULL, 0}
};

int		handle_algo(t_ssl *ssl, char *algo)
{
	int i;

	i = 0;
	while (g_algo[i].name && ft_strcmp(algo, g_algo[i].name))
		i++;
	if (!g_algo[i].name)
		return (err(ALGO, algo));
	ssl->algo_name = g_algo[i].name;
	ssl->algo = g_algo[i].algo;
	ssl->name_render = g_algo[i].name_render;
	ssl->len_hash = g_algo[i].len_hash;
	return (1);
}
