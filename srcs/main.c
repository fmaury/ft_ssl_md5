/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:46:59 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/03 15:07:25 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int	main(int ac, char **av)
{
	t_ssl ssl;

	if (ac < 2)
	{
		ft_dprintf(2, "usage: ft_ssl [-pqrs] input\n");
		return (1);
	}
	ft_bzero(&ssl, sizeof(t_ssl));
	if (!parse_arg(&ssl, av))
		return (1);
	
	return (0);
}
