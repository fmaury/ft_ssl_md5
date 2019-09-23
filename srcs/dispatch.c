/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 15:11:24 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/23 13:55:29 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int	stdin_buf(t_ssl *ssl)
{
	char	buf[200];
	int		len;
	char	*str;

	str = NULL;
	while ((len = read(0, buf, 150)))
	{
		if (len == -1)
			return (err(READ, ""));
		str = ft_strlf1join(str, buf, ssl->size, len);
		ssl->size += len;
	}
	ssl->plain = (void*)str;
	ssl->algo(ssl);
	return (1);
}

int	close_and_error(enum e_errtype	type, char *file, int fd)
{
	if (close(fd) < 0)
		return (err(CLOSE, file));
	return (err(type, file));
}

int	handle_file(t_ssl *ssl, char *file)
{
	int				fd;
	struct stat		fs;

	fd = 0;
	if ((fd = open(file, O_RDONLY)) < 0)
		return (err(OPEN, file));
	if (fstat(fd, &fs) < 0)
		return (close_and_error(FSTAT, file, fd));
	if ((fs.st_mode & S_IFMT) == S_IFDIR)
		return (close_and_error(DIRECTORY, file, fd));
	ssl->size = fs.st_size;
	if ((ssl->plain = mmap(0, ssl->size, PROT_READ | PROT_WRITE
	, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (close_and_error(MMAP, file, fd));
	if (close(fd) < 0)
		return (err(CLOSE, file));
	ssl->algo(ssl);
	return (1);
}

int	dispatch(t_ssl *ssl, char *plain)
{
	ssl->name = plain;
	if (!plain || ssl->flag & P_FLG)
		stdin_buf(ssl);
	else if (ssl->flag & S_FLG)
	{
		ssl->plain = (void*)plain;
		ssl->size = ft_strlen(plain);
		ssl->algo(ssl);
	}
	else
	{
		if (!handle_file(ssl, plain))
		{
			ssl->flag &= R_FLG;
			return (0);
		}
	}
	render(ssl);
	ssl->flag &= R_FLG;
	return (1);
}
