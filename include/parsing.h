/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish < ldurmish@student.42wolfsburg.d  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 16:22:41 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 21:20:48 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

typedef enum e_perr
{
	P_OK = 0,
	P_EARG,
	P_EOPEN,
	P_EREAD,
	P_EFMT,
	P_EDUP,
	P_EMISS,
	P_EINVAL,
	P_EMAP
}	t_perr;

int		parse_config(const char *path, t_config *out);
int		perr(t_perr code, const char *msg);
char	**read_all_line(int fd, int *output);

#endif
