# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldurmish <ldurmish@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/19 12:20:49 by ldurmish          #+#    #+#              #
#    Updated: 2025/01/13 19:59:13 by ldurmish         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the files
NAME = libft.a
PRINTF_NAME = libftprintf.a

# Compiler settings
CC = cc
CFLAGS = -Wall -Wextra -Werror -I include/ -I ft_printf/include/ -I gnl/include/

# Directories
LIBFT_DIR = src/
BONUS_DIR = bonus/
GNL_DIR = gnl/src/
GNL_BONUS_DIR = gnl/bonus/
PRINTF_DIR = ft_printf/src/

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

# Bonus files
BONUS_SRCS = $(BONUS_DIR)ft_lstnew_bonus.c $(BONUS_DIR)ft_lstadd_front_bonus.c $(BONUS_DIR)ft_lstsize_bonus.c \
             $(BONUS_DIR)ft_lstlast_bonus.c $(BONUS_DIR)ft_lstadd_back_bonus.c $(BONUS_DIR)ft_lstdelone_bonus.c \
             $(BONUS_DIR)ft_lstclear_bonus.c $(BONUS_DIR)ft_lstiter_bonus.c $(BONUS_DIR)ft_lstmap_bonus.c \
			 $(GNL_BONUS_DIR)get_next_line_bonus.c $(GNL_BONUS_DIR)get_next_line_utils_bonus.c \

# Ft_printf files
PRINTF_SRCS = $(PRINTF_DIR)check_error.c $(PRINTF_DIR)ft_handle_char.c $(PRINTF_DIR)ft_handle_hex.c \
				$(PRINTF_DIR)ft_handle_percentage.c $(PRINTF_DIR)ft_handle_ptr.c $(PRINTF_DIR)ft_handle_string.c \
				$(PRINTF_DIR)ft_handling_padding.c $(PRINTF_DIR)ft_init_print.c $(PRINTF_DIR)ft_print_width.c \
				$(PRINTF_DIR)ft_printf.c $(PRINTF_DIR)ft_putnbr.c \

# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
PRINTF_OBJS = $(PRINTF_SRCS:.c=.o)

# Headers
HEADERS = include/libft.h ft_printf/include/ft_printf.h gnl/include/get_next_line.h

# Main target
all: $(NAME) $(PRINTF_NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(BONUS_OBJS) $(NAME)
	ar rcs $(NAME) $(BONUS_OBJS)

$(PRINTF_NAME): $(PRINTF_OBJS)
	ar rcs $(PRINTF_NAME) $(PRINTF_OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) $(PRINTF_NAME)

re: fclean all clean

.PHONY: all clean fclean re bonus
