/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:35:46 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/08 11:52:09 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_check_error(const char *format, int pos)
{
	int	p_count;
	int	i;

	i = pos;
	p_count = 0;
	while (format[i] && !ft_strchr("cspdiuoxX%", format[i]))
	{
		if (format[i] == '.')
			p_count += 1;
		i++;
	}
	if (p_count > 1)
		return (1);
	return (0);
}

static void	ft_setflags(t_print *print)
{
	if (print->hash)
		print->length += write(1, "#", 1);
	if (print->plus)
		print->length += write(1, "+", 1);
	if (print->space && !print->plus)
		print->length += write(1, " ", 1);
	if (print->dash)
		print->length += write(1, "-", 1);
	if (print->zero && !print->dash)
		print->length += write(1, "0", 1);
}

int	ft_error_handle(t_print *print, const char *format, int pos)
{
	print->length += write(1, "%", 1);
	ft_setflags(print);
	while (format[pos] && format[pos] != '%')
	{
		print->length += write(1, &format[pos], 1);
		pos++;
	}
	if (format[pos] == '%')
		ft_init_print(print);
	return (pos - 1);
}
