# ---------------------
#  Project settings
#  --------------------
NAME = cub3d
TEST_NAME = cub3d_test
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib/libft/include -Ilib/mlx -Ilib/libft/gnl/include

# ----------------
#  Directories
#  --------------
SCR_DIR := src
PARSING_DIR := $(SCR_DIR)/parsing
EXECUTION_DIR := $(SCR_DIR)/execution
LIBFT_DIR := lib/libft
MLX_DIR := lib/mlx


# ---------------
#  Source files
#  -------------
SRCS = \
	   $(SCR_DIR)/main.c \
	   $(PARSING_DIR)/init_config.c $(PARSING_DIR)/parse_config.c $(PARSING_DIR)/errors.c \
	   $(PARSING_DIR)/files_utils.c $(PARSING_DIR)/parse_colors.c $(PARSING_DIR)/map_validate.c \
	   $(PARSING_DIR)/parse_identifiers.c $(PARSING_DIR)/parse_map.c $(PARSING_DIR)/parse_textures.c \
	   $(PARSING_DIR)/parse_utils.c $(PARSING_DIR)/parse_identifiers_utils.c $(PARSING_DIR)/map_validate_utils.c\
	   $(EXECUTION_DIR)/game.c $(EXECUTION_DIR)/raycasting.c $(EXECUTION_DIR)/rendering.c \
	   $(EXECUTION_DIR)/player.c $(EXECUTION_DIR)/input.c $(EXECUTION_DIR)/utils.c \

TEST_SRCS = \
	   $(SCR_DIR)/test_main.c \
	   $(PARSING_DIR)/init_config.c \
	   $(EXECUTION_DIR)/game.c $(EXECUTION_DIR)/raycasting.c $(EXECUTION_DIR)/rendering.c \
	   $(EXECUTION_DIR)/player.c $(EXECUTION_DIR)/input.c $(EXECUTION_DIR)/utils.c \
	   $(EXECUTION_DIR)/test_setup.c \

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# -------------
#  Libraries
#  ------------
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# ----------
#  Rules
#  ---------
all: $(NAME)

test: $(TEST_NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(TEST_NAME): $(TEST_OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(TEST_NAME)

# Compile  C -> OBJ
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	-$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	-$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all test clean fclean re
