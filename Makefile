# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eberkau <eberkau@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 16:25:19 by zbabic            #+#    #+#              #
#    Updated: 2025/12/06 04:50:17 by eberkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -ldl -lglfw -pthread -lm -L"/opt/homebrew/opt/glfw/lib/" #macOS
#LFLAGS = -L ./MLX42 -ldl -lglfw -lm -pthread -lGL #linux
COMPILER_DEBUG_ENABLED = -g
C_MAKE_DEBUG = -DDEBUG=1
REMOVE = rm -rf
NAME = cub3d

LIBMLX_REPO_URL = https://github.com/codam-coding-college/MLX42.git

SRC_FOLDER = src
OBJ_FOLDER = obj
INC_FOLDER = inc
LIBFT_FOLDER = libft
LIBMLX_FOLDER = MLX42

INCLUDES = -I$(INC_FOLDER) -I$(LIBFT_FOLDER) -I$(LIBMLX_FOLDER)/include/MLX42

LIBMLX_FILE = $(LIBMLX_FOLDER)/build/libmlx42.a
LIBFT_FILE = $(LIBFT_FOLDER)/libft.a
SRC_FILES = parsing/file_elements_parsing.c \
			parsing/file_parsing.c \
			parsing/file_single_element_parsing.c \
			parsing/map_linked_list.c \
			parsing/map_parsing.c \
			parsing/map_validation.c \
			parsing/texture_loading.c \
			rendering/elements_rendering.c \
			rendering/line_rendering.c \
			rendering/scene_rendering.c \
			rendering/ray_rendering.c \
			rendering/texture_rendering.c \
			env.c \
			error.c \
			game_loop.c \
			main.c \
			map.c \
			minimap.c \
			mlx_key_handlers.c \
			mlx_operations.c \
			player.c \
			raycasting.c \
			raycasting_utils.c \
			utilities.c \

OBJ_FILES = $(addprefix $(OBJ_FOLDER)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(LIBMLX_FILE) $(LIBFT_FILE) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBMLX_FILE) $(LIBFT_FILE) $(LFLAGS) -o $@

$(LIBMLX_FOLDER):
	@git clone $(LIBMLX_REPO_URL) $(LIBMLX_FOLDER)

$(LIBMLX_FILE): $(LIBMLX_FOLDER)
	@cmake $(LIBMLX_FOLDER) $(C_MAKE_DEBUG) -B $(LIBMLX_FOLDER)/build
	$(MAKE) -C $(LIBMLX_FOLDER)/build -j4

$(LIBFT_FILE):
	$(MAKE) -C $(LIBFT_FOLDER)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c | $(OBJ_FOLDER)
	$(CC) $(CFLAGS) $(COMPILER_DEBUG_ENABLED) $(INCLUDES) -c $< -o $@

$(OBJ_FOLDER):
	@mkdir -p $@
	@mkdir -p $@/parsing
	@mkdir -p $@/rendering

delete_repo:
	$(REMOVE) $(LIBMLX_FOLDER)

clean:
	$(MAKE) -C $(LIBFT_FOLDER) clean
	$(REMOVE) $(OBJ_FOLDER)
	$(REMOVE) $(LIBMLX_FOLDER)/build

fclean: clean
	$(MAKE) -C $(LIBFT_FOLDER) fclean
	$(REMOVE) $(NAME)
	$(MAKE) delete_repo

re: fclean all

.PHONY: clean fclean all re delete_repo