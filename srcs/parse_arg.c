/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:42:33 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/24 15:50:06 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int		flag(t_ssl *ssl, char c, char *f)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(f))
	{
		if (f[i] == c)
		{
			ssl->flag |= (0x00000000000000FF << (i * 8));
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
	if (ft_strlen(s) > 1)
		return (err(FLAG, s));
	if (!flag(ssl, s[i], "pqrs"))
		return (err(FLAG, s));
	return (1);
}

int		parse_arg(t_ssl *ssl, char **av)
{
	int		i;
	bool	catch;

	i = 2;
	catch = false;
	while (av[i])
	{
		if (!catch && !ft_strcmp("--", av[i]))
			catch = true;
		else if (!catch && av[i][0] == '-')
		{
			handle_flag(ssl, av[i] + 1);
			if (ssl->flag & S_FLG)
			{
				catch = true;
				if (!av[i + 1])
				{
					err(REQARG, (char*)ssl->algo_name);
					ssl->flag &= ~S_FLG;
					if ((P_FLG & ssl->flag))
						catch = false;
				}
			}
		}
		else
		{
			catch = true;
			dispatch(ssl, av[i], 1);
		}
		i++;
	}
	if (!catch)
	{
		if (!(P_FLG & ssl->flag))
			dispatch(ssl, av[i], 0);
		else
			dispatch(ssl, av[i], 1);
	}
	return (1);
}
