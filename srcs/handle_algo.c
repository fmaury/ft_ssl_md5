/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 15:57:59 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/04 15:59:13 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static t_algo		g_algo[] = {
	{"md5", md5},
	{"sha256", sha256},
	{NULL, NULL}
};

int		handle_algo(t_ssl *ssl, char *algo)
{
	int i;

	i = 0;
	while (g_algo[i].name && ft_strcmp(algo, g_algo[i].name))
		i++;
	if (!g_algo[i].name)
		return (err(ALGO, algo));
	ssl->algo = g_algo[i].func;
	return (1);
}
