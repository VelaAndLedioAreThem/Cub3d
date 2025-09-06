/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:55:25 by ldurmish          #+#    #+#             */
/*   Updated: 2025/01/17 14:38:09 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "../include/libft.h"
# include <limits.h>

typedef struct ft_printf
{
	va_list		args;
	int			dash;
	int			zero;
	int			point;
	int			plus;
	int			space;
	int			hash;
	int			width;
	int			length;
	int			precision;
	int			baselen;
	char		specifier;
	char		*base;
	int			base_n;
}	t_print;

int								ft_printf(const char *str, ...);
void							ft_handle_char(t_print *print);
int								ft_get_width(t_print *print,
									const char *str, int pos);
int								ft_get_precision(t_print *print,
									const char *str, int pos);
void							ft_putnum_base(long int n, char *base);
int								ft_len_base(long int n, int base);
void							ft_pad_zeros(t_print *print, int len);
void							ft_right_align(t_print *print, int len);
void							ft_left_align(t_print *print, int len);
void							ft_handle_percentage(t_print *print);
void							ft_handle_pointer(t_print *print);
void							ft_init_print(t_print *print);
int								ft_error_handle(t_print *print,
									const char *format, int pos);
int								ft_check_error(const char *format, int pos);
void							ft_put_nbr_un(t_print *print);
void							ft_print_hex(t_print *print);
void							ft_putchar(char c);
void							ft_handle_string(t_print *print);
void							ft_put_nbr(t_print *print);

#endif