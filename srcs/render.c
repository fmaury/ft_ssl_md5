/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:16:12 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/23 15:40:13 by fmaury           ###   ########.fr       */
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
	write(1, "\n", 1);
}

void	print_infos(t_ssl *ssl)
{
	ft_printf("%c%s%c", ssl->flag & S_FLG ? 34 : 0, ssl->name, \
	ssl->flag & S_FLG ? 34 : 0);
}

int		render(t_ssl *ssl)
{
	if (ssl->flag & P_FLG)
	{
		write(1, ssl->plain, ssl->size);
		print_hash(ssl);
	}
	else if (ssl->flag & R_FLG)
	{
		print_hash(ssl);
		write(1, " ", 2);
		print_infos(ssl);
	}
	else
	{
		ft_printf("%s(", ssl->name_render);
		print_infos(ssl);
		write(1, ssl->end_render, ft_strlen(ssl->end_render));
		print_hash(ssl);
	}
	return (1);
}
