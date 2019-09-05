/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:42:33 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/05 13:12:17 by fmaury           ###   ########.fr       */
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
	bool	catch_flag;

	i = 2;
	catch_flag = true;
	if (!av[i])
		ssl->flag |= P_FLG;
	while (av[i])
	{
		if (!ft_strcmp(av[i], "--"))
			catch_flag = false;
		else if (catch_flag == false || !ft_strcmp(av[i], "-") \
		|| av[i][0] != '-' || (ssl->flag & S_FLG))
			dispatch(ssl, av[i]);
		else
		{
			if (!handle_flag(ssl, av[i] + 1))
				return (0);
		}
		i++;
	}
	if (ssl->flag & P_FLG)
		dispatch(ssl, av[i]);
	return (1);
}
