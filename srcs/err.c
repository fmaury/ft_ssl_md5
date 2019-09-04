/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:04:03 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/04 15:26:19 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

static t_err	g_err[] = {
	{OPEN, "Open failed"},
	{CLOSE, "Close failed"},
	{DIRECTORY, "Is a directory"},
	{MALLOC, "Malloc failed"},
	{FLAG, "Illegal option"},
	{ALGO, "Unknow hash algorithm"},
	{READ, "Read failed"},
	{FSTAT, "Fstat failed"},
	{MMAP, "Mmap failed"},
	{DEFAULT_ERR, "Something wrong happened"},
};

int	err(enum e_errtype	type, char *filename)
{
	int i;

	i = 0;
	(void)err;
	(void)filename;
	(void)type;
	while (g_err[i].type != DEFAULT_ERR && g_err[i].type != type)
		i++;
	ft_dprintf(2, "ft_ssl: %s: %s\n", filename ? filename : "",
	g_err[i].mess);
	return (0);
}
