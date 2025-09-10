# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ledio <ledio@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 12:20:49 by ldurmish          #+#    #+#              #
#    Updated: 2025/09/10 21:33:34 by ldurmish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror -I include

SRCS = src/ft_bzero.c src/ft_calloc.c src/ft_isalnum.c \
		src/ft_isalpha.c src/ft_isascii.c src/ft_isdigit.c src/ft_isprint.c \
		src/ft_itoa.c src/ft_memchr.c src/ft_memcmp.c \
		src/ft_memcpy.c src/ft_memmove.c src/ft_memset.c src/ft_putchar_fd.c \
		src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_putstr_fd.c src/ft_split.c \
		src/ft_strchr.c src/ft_strdup.c src/ft_striteri.c src/ft_strjoin.c \
		src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strmapi.c \
		src/ft_strncmp.c src/ft_strnstr.c src/ft_strrchr.c src/ft_strtrim.c \
		src/ft_substr.c src/ft_tolower.c src/ft_toupper.c src/ft_atoi.c\


OBJS = $(SRCS:.c=.o)

HEADERS = include/libft.h

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(BONUS_OBJS)


fclean: clean
	rm -f $(NAME) $(BONUS_NAME)


re: fclean all clean


.PHONY: all clean fclean re
