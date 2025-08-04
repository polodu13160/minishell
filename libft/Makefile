.PHONY: all clean fclean re bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

NAME = libft.a

LIBFT_DIR = sources/

SRCS = $(addprefix $(LIBFT_DIR), \
       ft_isalpha.c \
       ft_printf_fd.c \
       ft_isdigit.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_strlen.c \
       ft_aclen.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strcpy.c \
       ft_strlcat.c \
       ft_strcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_atoi.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_strdup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_calloc.c \
       ft_isalnum.c \
       ft_itoa.c \
       ft_atoll.c \
       ft_strtrim.c \
       ft_putnbr_fd.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_strtrim.c \
       ft_putendl_fd.c \
       ft_split.c \
       ft_strmapi.c \
       ft_striteri.c \
       ft_printspecifier.c \
       ft_printf.c \
       ft_print_hexa.c \
       ft_printf_format.c \
       get_next_line.c \
       ft_strcmp.c \
       get_next_line_utils.c \
       ft_lstadd_back_bonus.c \
       ft_lstadd_front_bonus.c \
       ft_lstclear_bonus.c \
       ft_lstdelone_bonus.c \
       ft_lstiter_bonus.c \
       ft_lstlast_bonus.c \
       ft_lstnew_bonus.c \
       ft_lstsize_bonus.c \
       ft_strjoin3.c \
       ft_lstmap_bonus.c \
       ft_isalpha_space.c \
       ft_is_whitespace.c)

OBJ_DIR = obj/
OBJS = $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(OBJ_DIR)%.o: $(LIBFT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(OBJ_DIR)
	ar rc $(NAME) $(OBJS)
	@mkdir -p $(OBJ_DIR)
	ranlib $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re