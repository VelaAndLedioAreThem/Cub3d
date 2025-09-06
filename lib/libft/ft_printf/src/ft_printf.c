/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 21:14:04 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/10 13:03:15 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_format(t_print *print, const char *format, int pos)
{
	print->specifier = format[pos];
	if (format[pos] == 'c')
		ft_handle_char(print);
	else if (format[pos] == 's')
		ft_handle_string(print);
	else if (format[pos] == 'p')
		ft_handle_pointer(print);
	else if (format[pos] == 'd' || format[pos] == 'i')
		ft_put_nbr(print);
	else if (format[pos] == 'u')
		ft_put_nbr_un(print);
	else if (format[pos] == 'x' || format[pos] == 'X' || format[pos] == 'o')
		ft_print_hex(print);
	else if (format[pos] == '%')
		ft_handle_percentage(print);
}

static int	ft_check_flags(t_print *print, const char *format, int pos)
{
	while (ft_strchr("0-+# ", format[pos]))
	{
		if (format[pos] == '0')
			print->zero = 1;
		if (format[pos] == '-')
			print->dash = 1;
		if (format[pos] == '+')
			print->plus = 1;
		if (format[pos] == '#')
			print->hash = 1;
		if (format[pos] == ' ')
			print->space = 1;
		pos++;
	}
	return (pos);
}

static int	ft_parse_format(t_print *print, const char *format, int pos)
{
	int	start;
	int	err_handle;

	err_handle = 0;
	start = pos;
	pos = ft_check_flags(print, format, pos);
	err_handle = ft_check_error(format, start);
	if (!err_handle && ft_strchr("cspdiuoxX%123456789.", format[pos]))
	{
		while (format[pos + 1] && !ft_strchr("cspdiuoxX%", format[pos]))
		{
			if (ft_isdigit(format[pos]) && !(print->point))
				pos = ft_get_width(print, format, pos);
			if (format[pos] == '.')
			{
				print->point = 1;
				pos = ft_get_precision(print, format, pos + 1);
			}
			pos++;
		}
		ft_print_format(print, format, pos);
		return (pos);
	}
	pos = ft_error_handle(print, format, pos);
	return (pos);
}

int	ft_printf(const char *format, ...)
{
	t_print	*print;
	int		i;
	int		count;

	i = -1;
	count = 0;
	if (!format)
		return (-1);
	print = (t_print *)malloc(sizeof(t_print));
	if (!print)
		return (-1);
	ft_init_print(print);
	print->length = 0;
	va_start(print->args, format);
	while (format[++i])
	{
		if (format[i] == '%')
			i = ft_parse_format(print, format, i + 1);
		else
			count += write(1, &format[i], 1);
	}
	va_end(print->args);
	count += print->length;
	free(print);
	return (count);
}
