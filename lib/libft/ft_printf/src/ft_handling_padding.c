/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handling_padding.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:45:40 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/08 11:50:57 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_pad_zeros(t_print *print, int len)
{
	int	i;

	i = 0;
	if (print->precision > print->baselen)
	{
		while (i < (print->precision - print->baselen))
		{
			print->length += write(1, "0", 1);
			i++;
		}
	}
	else if (!(print->precision > print->baselen))
	{
		while (i < (print->width - len))
		{
			print->length += write(1, "0", 1);
			i++;
		}
	}
}

void	ft_right_align(t_print *print, int len)
{
	int	i;

	i = 0;
	if (print->precision > print->baselen)
	{
		while (i < (print->width - (print->precision - print->baselen) - len))
		{
			print->length += write(1, " ", 1);
			i++;
		}
	}
	else if (!(print->precision > print->baselen))
	{
		while (i < (print->width - len))
		{
			print->length += write(1, " ", 1);
			i++;
		}
	}
}

void	ft_left_align(t_print *print, int len)
{
	int	i;

	i = 0;
	if (print->precision > print->baselen)
	{
		while (i < (print->width - (print->precision - print->baselen) - len))
		{
			print->length += write(1, " ", 1);
			i++;
		}
	}
	else if (!(print->precision > print->baselen))
	{
		while (i < (print->width - len))
		{
			print -> length += write(1, " ", 1);
			i++;
		}
	}
}
