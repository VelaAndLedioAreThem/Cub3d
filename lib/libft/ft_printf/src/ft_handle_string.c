/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:32:55 by ldurmish          #+#    #+#             */
/*   Updated: 2024/07/08 11:52:28 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_string(t_print *print)
{
	char	*str;
	int		i;
	int		len;

	i = -1;
	str = va_arg(print->args, char *);
	if ((!str && print->precision >= 6) || (!str && !print->point))
		str = "(null)";
	if (!str && print->point && print->precision < 6)
		str = "";
	len = ft_strlen(str);
	print->baselen = len;
	if (print->point)
		print->baselen = print->precision;
	if (print->point && print->precision < len)
		len = print->precision;
	if (print->width && !print->dash)
		ft_right_align(print, len);
	while (str[++i] && i < len)
		print->length += write(1, &str[i], 1);
	if (print->width && print->dash)
		ft_left_align(print, len);
	ft_init_print(print);
}
