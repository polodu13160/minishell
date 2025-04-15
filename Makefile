.PHONY= all clean re fclean

CC = cc 
CFLAGS = -Wall -Wextra 
NAME = minishell
SRCS = main.c \
		tokenized.c \
		count_tokens.c \
		ft_echo.c \
		cd.c

OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

LIBFT_DIR = new_libft/
LIBFT = $(LIBFT_DIR)libft.a

HEADERS = token.h function.h

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)%.o: %.c $(HEADERS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all