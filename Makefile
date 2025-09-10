# ---------------------
#  Project settings
#  --------------------
NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib/libft/include -Ilib/mlx -Ilib/libft/gnl/include

# ----------------
#  Directories
#  --------------
SCR_DIR = src
PARSING_DIR = $(SCR_DIR)/parsing
EXECUTION_DIR = $(SCR_DIR)/execution
LIBFT_DIR = lib/libft
MLX_DIR = lib/mlx


# ---------------
#  Source files
#  -------------
SRCS = \
	   $(SCR_DIR)/main.c \
	   $(PARSING_DIR)/init_config.c $(PARSING_DIR)/parse_config.c $(PARSING_DIR)/errors.c \
	   $(PARSING_DIR)/files_utils.c \

OBJS = $(SRCS:.c=.o)

# -------------
#  Libraries
#  ------------
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

#  Linux linking
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ----------
#  Rules
#  ---------
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

# Compile  C -> OBJ
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	-$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME)
	-$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
