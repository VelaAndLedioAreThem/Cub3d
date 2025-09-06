/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:39:52 by ldurmish          #+#    #+#             */
/*   Updated: 2025/02/03 14:57:53 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "../include/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s__gnl_list
{
	char				*data;
	int					len;
	struct s__gnl_list	*next;
	int					to_delete;
	int					found_newline;
}				t_gnl_list;

typedef struct s_glfl
{
	char			*tmp;
	char			*line;
	char			*new_line;
	char			*part;
	t_gnl_list		*temp;
}			t_glfl;
char						*get_next_line(int fd);
void						ft_add_node(t_gnl_list **head, char *str);
void						ft_remove_data(t_gnl_list **head);
void						*ft_clear_list(t_gnl_list **list,
								t_gnl_list *clean_node, char *buf, int del_one);
#endif
