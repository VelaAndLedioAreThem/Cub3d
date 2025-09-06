/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 23:10:28 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/07 18:50:38 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex_rec(t_print *print)
{
	if (print->specifier == 'x')
		write(1, "0x", 2);
	if (print->specifier == 'X')
		write(1, "0X", 2);
	if (print->specifier == 'o' && print->baselen >= print->precision)
		write(1, "0", 1);
}

static void	ft_print_hex_prefix(t_print *print)
{
	if (print->specifier == 'x')
	{
		print->base = "0123456789abcdef";
		print->base_n = 16;
	}
	if (print->specifier == 'X')
	{
		print->base = "0123456789ABCDEF";
		print->base_n = 16;
	}
	if (print->specifier == 'o')
	{
		print->base = "01234567";
		print->base_n = 8;
	}
}

static int	ft_hex_helper(t_print *print, int len, unsigned int n)
{
	if (print->hash && n != 0 && print->specifier != 'o')
		len += 2;
	else if (print->hash && n != 0 && print->specifier == 'o'
		&& print->baselen >= print->precision)
		len += 1;
	if ((print->width && !print->dash) && (!print->zero || print->point))
		ft_right_align(print, len);
	if (print->hash && n != 0)
		ft_puthex_rec(print);
	if ((print->zero && !print->dash && !print->point)
		|| (print->precision > print->baselen))
		ft_pad_zeros(print, len);
	return (len);
}

void	ft_print_hex(t_print *print)
{
	unsigned int	n;
	int				len;

	n = (unsigned int)va_arg(print->args, unsigned int);
	ft_print_hex_prefix(print);
	print->baselen = ft_len_base(n, print->base_n);
	len = print->baselen;
	if (!n && !print->precision && print->point)
		len--;
	len = ft_hex_helper(print, len, n);
	if (n != 0 || (n == 0 && (!print->point || print->precision)))
		ft_putnum_base(n, print->base);
	if (print->dash)
		ft_left_align(print, len);
	print->length += len;
	ft_init_print(print);
}
