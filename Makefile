.PHONY= all clean re fclean

CC = cc 
CFLAGS = -Wall -Wextra -MMD -MP -I$(LIBFT_DIR)/includes -Iincludes
NAME = minishell
SRCS = main \
		tokenized \
		tokenized_more \
		tokenized_more2 \
		count_tokens \
		ft_echo \
		cd

OBJ_DIR = objects/
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRCS)))

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
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all