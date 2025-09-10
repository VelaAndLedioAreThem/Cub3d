# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 12:20:49 by ldurmish          #+#    #+#              #
#    Updated: 2025/09/10 22:11:37 by ldurmish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the files
NAME = libft.a

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include/ -I gnl/include/

# Directories
GNL_DIR = gnl/src/

# Source files
SRCS = $(LIBFT_DIR)ft_bzero.c $(LIBFT_DIR)ft_calloc.c $(LIBFT_DIR)ft_isalnum.c \
		$(LIBFT_DIR)ft_isalpha.c $(LIBFT_DIR)ft_isascii.c $(LIBFT_DIR)ft_isdigit.c \
		$(LIBFT_DIR)ft_isprint.c $(LIBFT_DIR)ft_itoa.c $(LIBFT_DIR)ft_memchr.c \
		$(LIBFT_DIR)ft_memcmp.c $(LIBFT_DIR)ft_memcpy.c $(LIBFT_DIR)ft_memmove.c \
		$(LIBFT_DIR)ft_memset.c $(LIBFT_DIR)ft_putchar_fd.c $(LIBFT_DIR)ft_putendl_fd.c \
		$(LIBFT_DIR)ft_putnbr_fd.c $(LIBFT_DIR)ft_putstr_fd.c $(LIBFT_DIR)ft_split.c \
		$(LIBFT_DIR)ft_strchr.c $(LIBFT_DIR)ft_strdup.c $(LIBFT_DIR)ft_striteri.c \
		$(LIBFT_DIR)ft_strjoin.c $(LIBFT_DIR)ft_strlcat.c $(LIBFT_DIR)ft_strlcpy.c \
		$(LIBFT_DIR)ft_strlen.c $(LIBFT_DIR)ft_strmapi.c $(LIBFT_DIR)ft_strncmp.c \
		$(LIBFT_DIR)ft_strnstr.c $(LIBFT_DIR)ft_strrchr.c $(LIBFT_DIR)ft_strtrim.c \
		$(LIBFT_DIR)ft_substr.c $(LIBFT_DIR)ft_tolower.c $(LIBFT_DIR)ft_toupper.c \
		$(LIBFT_DIR)ft_atoi.c $(GNL_DIR)get_next_line.c $(GNL_DIR)get_next_line_utils.c \


# Object files
OBJS = $(SRCS:.c=.o)

# Headers
HEADERS = include/libft.hgnl/include/get_next_line.h

# Main target
all: $(NAME) $(PRINTF_NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(PRINTF_NAME)

re: fclean all clean

.PHONY: all clean fclean re bonus
