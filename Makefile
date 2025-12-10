# ---------------------
#  Project settings
#  --------------------
NAME = cub3d
TEST_NAME = cub3d_test
CC = cc
CFLAGS = -Wall -g -Wextra -Werror -O2 -Iinclude -Ilib/libft/include -Ilib/mlx -Ilib/libft/gnl/include

# Minimal, readable build output
.SILENT:

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
SRCS_COMMON = \
	   $(SCR_DIR)/main.c \
	   $(PARSING_DIR)/init_config.c $(PARSING_DIR)/parse_config.c $(PARSING_DIR)/errors.c \
	   $(PARSING_DIR)/files_utils.c $(PARSING_DIR)/parse_colors.c $(PARSING_DIR)/map_validate.c \
	   $(PARSING_DIR)/parse_identifiers.c $(PARSING_DIR)/parse_map.c $(PARSING_DIR)/parse_textures.c \
	   $(PARSING_DIR)/parse_identifiers_utils_1.c \
	   $(PARSING_DIR)/parse_utils.c $(PARSING_DIR)/parse_identifiers_utils.c $(PARSING_DIR)/map_validate_utils.c\
	   $(EXECUTION_DIR)/game.c $(EXECUTION_DIR)/raycasting.c \
	   $(EXECUTION_DIR)/ray_math.c $(EXECUTION_DIR)/raycast_h.c $(EXECUTION_DIR)/raycast_v.c \
	   $(EXECUTION_DIR)/render_background.c $(EXECUTION_DIR)/render_walls.c \
	   $(EXECUTION_DIR)/texture.c \
	   $(EXECUTION_DIR)/player.c $(EXECUTION_DIR)/input.c \
	   $(EXECUTION_DIR)/utils.c \
	   $(EXECUTION_DIR)/keys.c \
	   $(EXECUTION_DIR)/init.c \
	   $(EXECUTION_DIR)/hooks.c $(EXECUTION_DIR)/game_loop.c \
	   $(EXECUTION_DIR)/cleanup.c

SRCS_MAND = \
	   $(SRCS_COMMON) \
	   $(EXECUTION_DIR)/minimap.c \
	   $(EXECUTION_DIR)/hud.c \
	   $(EXECUTION_DIR)/mouse.c \
	   $(EXECUTION_DIR)/fullscreen.c

SRCS_BONUS = \
	   $(SRCS_COMMON) \
	   $(EXECUTION_DIR)/minimap_bonus.c \
	   $(EXECUTION_DIR)/hud_bonus.c \
	   $(EXECUTION_DIR)/mouse_bonus.c \
	   $(EXECUTION_DIR)/fullscreen_bonus.c

ifeq ($(BONUS),1)
SRCS = $(SRCS_BONUS)
else
SRCS = $(SRCS_MAND)
endif

TEST_SRCS = \
	   $(SCR_DIR)/test_main.c \
	   $(PARSING_DIR)/init_config.c \
	   $(EXECUTION_DIR)/game.c $(EXECUTION_DIR)/raycasting.c \
	   $(EXECUTION_DIR)/ray_math.c $(EXECUTION_DIR)/raycast_h.c $(EXECUTION_DIR)/raycast_v.c \
	   $(EXECUTION_DIR)/render_background.c $(EXECUTION_DIR)/render_walls.c $(EXECUTION_DIR)/texture.c \
	   $(EXECUTION_DIR)/player.c $(EXECUTION_DIR)/input.c $(EXECUTION_DIR)/utils.c \
	   $(EXECUTION_DIR)/minimap.c $(EXECUTION_DIR)/hud.c \
	   $(EXECUTION_DIR)/mouse.c $(EXECUTION_DIR)/keys.c \
	   $(EXECUTION_DIR)/init.c \
	   $(EXECUTION_DIR)/hooks.c $(EXECUTION_DIR)/game_loop.c $(EXECUTION_DIR)/fullscreen.c \
	   $(EXECUTION_DIR)/cleanup.c \
	   $(EXECUTION_DIR)/test_setup.c \

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

# -------------
#  Libraries
#  ------------
LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lXrandr -lm

# ----------
#  Rules
#  ---------
all: $(NAME)
	printf "DONE\n"

bonus:
	$(MAKE) fclean
	$(MAKE) BONUS=1 all
	printf "DONE (bonus)\n"

test: $(TEST_NAME)
	printf "DONE (test)\n"

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	printf "LD  %s\n" "$(NAME)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	printf "OK  %s\n" "$(NAME)"

$(TEST_NAME): $(TEST_OBJS) $(LIBFT) $(MLX)
	printf "LD  %s\n" "$(TEST_NAME)"
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT) $(MLX_FLAGS) -o $(TEST_NAME)
	printf "OK  %s\n" "$(TEST_NAME)"

# Compile  C -> OBJ
%.o: %.c
	printf "CC  %s\n" "$<"
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	printf "LIB %s\n" "libft"
	$(MAKE) -s -C $(LIBFT_DIR)

$(MLX):
	printf "LIB %s\n" "mlx"
	$(MAKE) -s -C $(MLX_DIR)

clean:
	printf "CLEAN objects\n"
	rm -f $(OBJS) $(TEST_OBJS)
	-$(MAKE) -s -C $(LIBFT_DIR) clean
	-$(MAKE) -s -C $(MLX_DIR) clean

fclean: clean
	printf "CLEAN binaries\n"
	rm -f $(NAME) $(TEST_NAME)
	-$(MAKE) -s -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all test clean fclean re
