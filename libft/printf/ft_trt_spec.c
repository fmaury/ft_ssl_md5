/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trt_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 10:52:51 by fmaury            #+#    #+#             */
/*   Updated: 2019/02/28 10:40:51 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_trt_spec(t_print *arg, t_flag *flag)
{
	char *str;

	str = NULL;
	if (arg->specifier == 'd' || arg->specifier == 'i'
	|| arg->specifier == 'D')
		str = ft_trt_int(arg, flag);
	else if (arg->specifier == 'o' || arg->specifier == 'O'
	|| arg->specifier == 'x' || arg->specifier == 'X'
	|| arg->specifier == 'u' || arg->specifier == 'U'
	|| arg->specifier == 'b' || arg->specifier == 'B')
		str = ft_trt_uxo(arg, flag);
	else if (arg->specifier == 'p')
		str = ft_trt_point(arg, flag);
	else if (arg->specifier == '%')
		str = ft_trt_percent(arg, flag);
	else if (arg->specifier == 'c' || arg->specifier == 'C')
		str = ft_trt_char(arg, flag);
	else if (arg->specifier == 's' || arg->specifier == 'S')
		str = ft_trt_str(arg, flag);
	else
		str = ft_trt_err(arg, flag);
	return (str);
}
