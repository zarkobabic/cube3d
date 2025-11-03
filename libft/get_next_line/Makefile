CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = get_next_line.a
LIBFT_DIR = ../
INCLUDES = -I$(LIBFT_DIR)

MY_C_SOURCES = 	get_next_line_bonus.c \
				get_next_line_utils_bonus.c \

MY_OBJECTS = $(MY_C_SOURCES:.c=.o)
REMOVE = rm -rf

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

fclean: clean
	$(REMOVE) $(NAME)

clean:
	$(REMOVE) $(MY_OBJECTS)

re: fclean
	$(MAKE) all

.PHONY: clean fclean all re
