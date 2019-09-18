/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 10:27:08 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/18 15:57:02 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_H
#define SSL_H

#include <libft.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdbool.h>

#define P_FLG 0x000000FF
#define Q_FLG 0x0000FF00
#define R_FLG 0x00FF0000
#define S_FLG 0xFF000000

enum				e_errtype
{
	USAGE,
	OPEN,
	CLOSE,
	DIRECTORY,
	MALLOC,
	FLAG,
	ALGO,
	READ,
	FSTAT,
	MMAP,
	DEFAULT_ERR,
};

typedef struct		s_err
{
	enum e_errtype	type;
	const char		*mess;
}					t_err;

typedef 			struct s_ssl
{
	char			*name;
	int				flag;
	int 			(*algo) (struct s_ssl *ssl);
	unsigned char	*plain;
	size_t			size;
	uint32_t		*hash;
}					t_ssl;

typedef struct		s_ctx
{
	unsigned char			data[64];
	unsigned int				datalen;
	size_t			bitlen;
	unsigned int			state[8];
}					t_ctx;

typedef struct		s_algo
{
	const char		*name;
	int 			(*func) (t_ssl *ssl);
}					t_algo;


int		parse_arg(t_ssl *ssl, char **av);
int		err(enum e_errtype	type, char *filename);
int		dispatch(t_ssl *ssl, char *plain);
int		md5(t_ssl *ssl);
int		sha256(t_ssl *ssl);
int		handle_algo(t_ssl *ssl, char *algo);
int		render(t_ssl *ssl);
uint32_t		leftrotate(uint32_t x, uint32_t c);
uint32_t		rightrotate(uint32_t x, uint32_t c);
uint32_t		ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t		maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t		ep0(uint32_t x);
uint32_t		ep1(uint32_t x);
uint32_t		sig0(uint32_t x);
uint32_t		sig1(uint32_t x);

#endif