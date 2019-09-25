/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:46:59 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/25 14:51:01 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int	main(int ac, char **av)
{
	t_ssl	ssl;

	if (ac < 2)
	{
		write(2, "usage: ft_ssl [md5|sha256] [-pqrs] input\n", 28);
		return (1);
	}
	ft_bzero(&ssl, sizeof(t_ssl));
	if (!handle_algo(&ssl, av[1]))
		return (1);
	if (!parse_arg(&ssl, av))
		return (1);
	return (0);
}
