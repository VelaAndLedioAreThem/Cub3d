/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ledio <ledio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:39:52 by ldurmish          #+#    #+#             */
/*   Updated: 2025/09/10 22:07:10 by ldurmish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list_gnl
{
	int					len;
	int					to_delete;
	int					found_newline;
	char				*data;
	struct s_list_gnl	*next;
}	t_list_gnl;

typedef struct s_glfl
{
	char			*tmp;
	char			*line;
	char			*new_line;
	char			*part;
	t_list_gnl		*temp;
}	t_glfl;

char							*get_next_line(int fd);
void							ft_add_node(t_list_gnl **head, char *str);
void							ft_remove_data(t_list_gnl **head);
void							*ft_clear_list(t_list_gnl **list,
									t_list_gnl *clean_node,
									char *buf, int del_one);
char							*ft_strchr(const char *s, int c);
char							*ft_strjoin(char *s1, char *s2);
char							*ft_strdup(const char *str);

#endif
