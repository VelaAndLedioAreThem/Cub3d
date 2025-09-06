/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:57:34 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/08 00:58:00 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_char(t_print *print)
{
	char	c;

	c = va_arg(print->args, int);
	if (print->width && !(print->dash))
		ft_right_align(print, 1);
	print->length += write(1, &c, 1);
	if (print->width && print->dash)
		ft_left_align(print, 1);
	ft_init_print(print);
}
