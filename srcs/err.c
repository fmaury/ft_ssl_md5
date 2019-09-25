/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:04:03 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/25 13:49:23 by fmaury           ###   ########.fr       */
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
	{MMAP, "Munmap failed"},
	{REQARG, "option requires an argument -- s"},
	{DEFAULT_ERR, "Something wrong happened"},
};

int	err(enum e_errtype	type, char *filename)
{
	int i;

	i = 0;
	while (g_err[i].type != DEFAULT_ERR && g_err[i].type != type)
		i++;
	write(2, "ft_ssl: ", 8);
	if (filename)
	{
		write(2, filename, ft_strlen(filename));
		write(2, ": ", 2);
	}
	write(2, g_err[i].mess, ft_strlen(g_err[i].mess));
	write(2, "\n", 1);
	return (0);
}
