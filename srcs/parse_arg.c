/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:42:33 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/03 15:07:54 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int		flag(t_ssl *ssl, char c)
{
	char	f[5];
	size_t	i;

	i = 0;
	ft_strcpy(f, "pqrs");
	while (i < ft_strlen(f))
	{
		if (f[i] == c)
		{
			ssl->flag |= (0x000000FF << (i * 8));
			return (1);
		}
		i++;
	}
	return (0);
}

int		handle_flag(t_ssl *ssl, char *s)
{
	size_t		i;

	i = 0;
	while (i < ft_strlen(s))
	{
		if (!flag(ssl, s[i]))
			return (err(FLAG, s));
		i++;
	}
	return (1);
}

int		parse_arg(t_ssl *ssl, char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "--") || !ft_strcmp(av[i], "-")
		|| av[i][0] != '-')
			return (1);
		handle_flag(ssl, av[i] + 1);
		i++;
	}
	ft_printf("%.8x\n", ssl->flag);
	return (1);
}
