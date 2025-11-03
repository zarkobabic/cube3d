CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
PRINTF_DIR = ft_printf/
PRINTF = $(PRINTF_DIR)printf.a
GET_NEXT_LINE_DIR = get_next_line/
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)get_next_line.a

MY_C_SOURCES = 	ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_strchr.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strrchr.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_striteri.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				$(PRINTF_DIR)ft_libft_utilities_for_printf.c \
				$(PRINTF_DIR)ft_printf_int_handling.c \
				$(PRINTF_DIR)ft_printf_ptr_handling.c \
				$(PRINTF_DIR)ft_printf_text_handling.c \
				$(PRINTF_DIR)ft_printf_uint_handling.c \
				$(PRINTF_DIR)ft_printf.c \
				$(PRINTF_DIR)ft_put_pointer_fd.c \
				$(GET_NEXT_LINE_DIR)get_next_line_bonus.c \
				$(GET_NEXT_LINE_DIR)get_next_line_utils_bonus.c

MY_OBJECTS = $(MY_C_SOURCES:.c=.o)
REMOVE = rm -rf

all: $(NAME)

$(NAME): $(PRINTF) $(GET_NEXT_LINE) $(MY_OBJECTS)
	ar rcs $(NAME) $(MY_OBJECTS)

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

$(GET_NEXT_LINE):
	$(MAKE) -C $(GET_NEXT_LINE_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	$(MAKE) -C $(PRINTF_DIR) fclean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) fclean
	$(REMOVE) $(NAME)

clean:
	$(MAKE) -C $(PRINTF_DIR) clean
	$(MAKE) -C $(GET_NEXT_LINE_DIR) clean
	$(REMOVE) $(MY_OBJECTS)

re: fclean all

.PHONY: clean fclean all re
