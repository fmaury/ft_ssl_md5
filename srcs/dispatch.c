/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:11:24 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/30 13:10:00 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int	stdin_buf(t_ssl *ssl, int flag)
{
	char			buf[200];
	int				ret;

	while ((ret = read(0, buf, 150)))
	{
		if (ret == -1)
			return (err(READ, ""));
		if (!(ssl->plain = ft_ustrljoin(ssl->plain, buf, ssl->size, ret)))
			return (err(MALLOC, ""));
		ssl->size += ret;
	}
	ssl->name = (void*)ssl->plain;
	ssl->algo(ssl);
	render(ssl, flag);
	free(ssl->plain);
	ssl->plain = NULL;
	ssl->size = 0;
	ssl->flag &= (~P_FLG);
	return (1);
}

int	close_and_error(enum e_errtype	type, char *file, int fd)
{
	if (close(fd) < 0)
		return (err(CLOSE, file));
	return (err(type, file));
}

int	handle_file(t_ssl *ssl, char *file, int flag)
{
	int				fd;
	char			buf[250];
	int				ret;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (err(OPEN, file));
	while ((ret = read(fd, buf, 250)) > 0)
	{
		if (!(ssl->plain = ft_ustrljoin(ssl->plain, buf, ssl->size, ret)))
			return (close_and_error(MALLOC, file, fd));
		ft_bzero(buf, ret);
		ssl->size += ret;
	}
	if (ret == -1)
		return (close_and_error(READ, file, fd));
	if (close(fd) < 0)
		return (err(CLOSE, file));
	ssl->algo(ssl);
	render(ssl, flag);
	free(ssl->plain);
	ssl->plain = NULL;
	return (1);
}

int	dispatch(t_ssl *ssl, char *plain, int flag)
{
	if (ssl->flag & P_FLG || !flag)
		stdin_buf(ssl, flag);
	if (ssl->flag & S_FLG)
	{
		ssl->name = plain;
		ssl->plain = (void*)plain;
		ssl->size = ft_strlen(plain);
		ssl->algo(ssl);
		render(ssl, flag);
		ssl->flag &= (~S_FLG);
	}
	else if (plain)
	{
		ssl->name = plain;
		if (!handle_file(ssl, plain, flag))
			return (0);
	}
	ssl->plain = NULL;
	ssl->size = 0;
	return (1);
}
