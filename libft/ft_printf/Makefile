CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = printf.a
LIBFT_DIR = ../
INCLUDES = -I$(LIBFT_DIR)

MY_C_SOURCES = 	ft_printf_int_handling.c \
				ft_printf_ptr_handling.c \
				ft_printf_text_handling.c \
				ft_printf_uint_handling.c \
				ft_printf.c \
				ft_put_pointer_fd.c \
				ft_libft_utilities_for_printf.c \

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

re: fclean all

.PHONY: clean fclean all re
