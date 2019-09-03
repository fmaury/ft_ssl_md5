/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:27:08 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/03 15:14:20 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
#define SSL_H

#include <libft.h>
#include <fcntl.h>

enum				e_errtype
{
	USAGE,
	OPEN,
	CLOSE,
	DIRECTORY,
	MALLOC,
	FLAG,
	DEFAULT_ERR,
};

enum				e_algo
{
	MD5,
	SHA256,
	DEFAULT_ALGO,
};

typedef struct		s_algo
{
	enum e_algo		algo;
	void			*func;
}					t_err;

typedef struct		s_err
{
	enum e_errtype	type;
	const char		*mess;
}					t_err;

typedef 			struct s_ssl
{
	char			*name;
	int				flag;
}					t_ssl;


int		parse_arg(t_ssl *ssl, char **av);
int		err(enum e_errtype	type, char *filename);
int		dispatch(t_ssl *ssl, char **av);

#endif