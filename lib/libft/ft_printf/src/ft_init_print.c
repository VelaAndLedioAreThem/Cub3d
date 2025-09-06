/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:48:20 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/06 13:00:36 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_print(t_print *print)
{
	print->dash = 0;
	print->zero = 0;
	print->point = 0;
	print->plus = 0;
	print->space = 0;
	print->hash = 0;
	print->width = 0;
	print->precision = 0;
	print->baselen = 0;
	print->specifier = 0;
	print->base = NULL;
	print->base_n = 0;
}
