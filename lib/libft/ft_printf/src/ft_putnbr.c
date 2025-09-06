/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 18:42:08 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/08 17:06:20 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_base(long int n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n)
	{
		n = n / base;
		len++;
	}
	return (len);
}

void	ft_putnum_base(long int n, char *base)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (n / base_len)
		ft_putnum_base(n / base_len, base);
	ft_putchar(base[n % base_len]);
}

static int	ft_print_nbr_util(t_print *print, int len, long int n)
{
	if (!n && !print->precision && print->point)
		len--;
	if (print->space && n >= 0 && !print->plus)
		len += write(1, " ", 1);
	if ((print->plus || n < 0))
		len++;
	if ((print->width && !print->dash) && (!print->zero || print->point))
		ft_right_align(print, len);
	if (print->plus && n >= 0)
		write(1, "+", 1);
	if (n < 0)
		ft_putchar('-');
	if (((print->zero && !print->dash) && !(print->point))
		|| (print->precision > print->baselen))
		ft_pad_zeros(print, len);
	return (len);
}

void	ft_put_nbr(t_print *print)
{
	long int	n;
	int			len;

	n = va_arg(print -> args, int);
	print->baselen = ft_len_base(n, 10);
	len = print->baselen;
	len = ft_print_nbr_util(print, len, n);
	if (n < 0)
		n = -n;
	if (n != 0 || (n == 0 && !(print->point && !print->precision)))
		ft_putnum_base(n, "0123456789");
	if (print->dash)
		ft_left_align(print, len);
	print->length += len;
	ft_init_print(print);
}

void	ft_put_nbr_un(t_print *print)
{
	long int	n;
	int			len;

	n = va_arg(print -> args, unsigned int);
	print->baselen = ft_len_base(n, 10);
	len = print->baselen;
	len = ft_print_nbr_util(print, len, n);
	if (n != 0 || (n == 0 && !(print->point && !print->precision)))
		ft_putnum_base(n, "0123456789");
	if (print->dash)
		ft_left_align(print, len);
	print->length += len;
	ft_init_print(print);
}
