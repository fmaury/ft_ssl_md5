/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 11:04:03 by fmaury            #+#    #+#             */
/*   Updated: 2019/09/03 15:07:36 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ssl.h>

int	err(enum e_errtype	type, char *filename)
{
	int i;
	t_err	err[] = {
		{OPEN, "Open failed"},
		{CLOSE, "Close failed"},
		{DIRECTORY, "Is a directory"},
		{MALLOC, "Malloc failed"},
		{FLAG, "illegal option"},
		{DEFAULT_ERR, "Something wrong happened"},
	};

	i = 0;
	(void)err;
	(void)filename;
	(void)type;
	while (err[i].type != DEFAULT_ERR && err[i].type != type)
		i++;
	ft_dprintf(2, "ft_ssl: %s: %s\n", filename ? filename : "", err[i].mess);
	return (0);
}
