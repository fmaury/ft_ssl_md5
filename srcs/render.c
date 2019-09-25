/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:16:12 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/25 13:27:30 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	print_hash(t_ssl *ssl)
{
	unsigned int	i;

	i = 0;
	while (i < ssl->len_hash)
	{
		ft_printf("%2.2x", ssl->hash[i]);
		i++;
	}
}

void	print_infos(t_ssl *ssl)
{
	ft_printf("%c%s%c", ssl->flag & S_FLG ? 34 : 0, ssl->name, \
	ssl->flag & S_FLG ? 34 : 0);
}

void	handle_render(t_ssl *ssl)
{
	if (!(ssl->flag & Q_FLG))
	{
		ft_printf("%s (", ssl->name_render);
		print_infos(ssl);
		write(1, ") = ", 4);
	}
	print_hash(ssl);
}

int		render(t_ssl *ssl, int flag)
{
	if (ssl->flag & P_FLG || !flag)
	{
		if (ssl->flag & P_FLG)
			write(1, ssl->plain, ssl->size);
		print_hash(ssl);
	}
	else if (ssl->flag & R_FLG)
	{
		print_hash(ssl);
		if (!(ssl->flag & Q_FLG))
		{
			write(1, " ", 2);
			print_infos(ssl);
		}
	}
	else
		handle_render(ssl);
	write(1, "\n", 1);
	free(ssl->hash);
	return (1);
}
