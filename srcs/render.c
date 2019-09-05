/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:16:12 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/05 13:14:26 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

void	print_hash(t_ssl *ssl)
{
	uint8_t *p;

	p = (uint8_t *)&ssl->hash[0];
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&ssl->hash[1];
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&ssl->hash[2];
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&ssl->hash[3];
	ft_printf("%2.2x%2.2x%2.2x%2.2x\n", p[0], p[1], p[2], p[3]);
	free(ssl->hash);
	ssl->hash = NULL;
}

void	print_infos(t_ssl *ssl)
{
	ft_printf("%c%s%c", ssl->flag & S_FLG ? 34 : 0, ssl->name, \
	ssl->flag & S_FLG ? 34 : 0);
}

int		render(t_ssl *ssl)
{
	if (ssl->flag & P_FLG)
		print_hash(ssl);
	else if (ssl->flag & R_FLG)
	{
		print_hash(ssl);
		write(1, " ", 2);
		print_infos(ssl);
	}
	else
	{
		write(1, "MD5 (", 5);
		print_infos(ssl);
		write(1, ") = ", 4);
		print_hash(ssl);
	}
	return (1);
}
