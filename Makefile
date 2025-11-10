# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zbabic <zbabic@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/03 16:25:19 by zbabic            #+#    #+#              #
#    Updated: 2025/11/10 21:36:12 by zbabic           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -ldl -lglfw -pthread -lm -L"/opt/homebrew/opt/glfw/lib/" #macOS
# LFLAGS = -L ./MLX42 -ldl -lglfw -lm -pthread -lGL #linux
COMPILER_DEBUG_ENABLED = -g
C_MAKE_DEBUG = -DDEBUG=1
REMOVE = rm -rf
NAME = cube3d

LIBMLX_REPO_URL = https://github.com/codam-coding-college/MLX42.git

SRC_FOLDER = src
OBJ_FOLDER = obj
INC_FOLDER = inc
LIBFT_FOLDER = libft
LIBMLX_FOLDER = MLX42

INCLUDES = -I$(INC_FOLDER) -I$(LIBFT_FOLDER) -I$(LIBMLX_FOLDER)/include/MLX42

LIBMLX_FILE = $(LIBMLX_FOLDER)/build/libmlx42.a
LIBFT_FILE = $(LIBFT_FOLDER)/libft.a
SRC_FILES = env.c \
			error.c \
			file_elements_parsing.c \
			file_parsing.c \
			file_single_element_parsing.c \
			main.c \
			map_linked_list.c \
			map_parsing.c \
			map_validation.c \
			map.c \
			mlx_operations.c \
			player.c \

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