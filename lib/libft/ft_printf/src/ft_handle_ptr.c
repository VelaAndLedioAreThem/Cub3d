/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:07:25 by ldurmish          #+#    #+#             */
/*   Updated: 2024/12/18 19:15:25 by ledio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static int	ft_len_base_ptr(unsigned long int n, int base)
{
	int	len;

	len = 0;
	if (!n)
		len = 5;
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

static void	ft_putnum_base_ptr(unsigned long int n, char *base)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (n / base_len)
		ft_putnum_base_ptr(n / base_len, base);
	ft_putchar(base[n % base_len]);
}

static void	ft_ptr_helper(t_print *print, unsigned long p)
{
	if (print->plus && p)
		write(1, "+", 1);
	if (p)
		write(1, "0x", 2);
	if (!p)
		write(1, "(nil)", 5);
}

void	ft_handle_pointer(t_print *print)
{
	int				len;
	unsigned long	p;

	p = (unsigned long)va_arg(print->args, void *);
	print->baselen = ft_len_base_ptr(p, 16);
	len = print->baselen;
	if (p)
		len += 2;
	if (print->plus && p)
		len++;
	if (!p)
		print->baselen = print->precision;
	if ((print->width && !print->dash) && (!print->zero || print->point || !p))
		ft_right_align(print, len);
	ft_ptr_helper(print, p);
	if ((print->zero && !print->dash && !print->point && p)
		|| ((print->precision > print->baselen) && p))
		ft_pad_zeros(print, len);
	if (p)
		ft_putnum_base_ptr(p, "0123456789abcdef");
	if (print->dash)
		ft_left_align(print, len);
	print -> length += len;
	ft_init_print(print);
}
