.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra -MMD -MP -I$(LIBFT_DIR)includes -Iincludes -g3
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 

NAME = minishell
FILES = main \
		tokenized \
		tokenized_more \
		tokenized_more2 \
		count_tokens \
		ft_echo \
		cd \
		ast \
		check_here_doc \
		check_fd

OBJ_DIR = objects/
SRC_DIR = sources/
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

LIBFT_DIR = new_libft/
LIBFT = $(LIBFT_DIR)libft.a


all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT):  FORCE
	$(MAKE) -C $(LIBFT_DIR)
FORCE:

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(CFLAGS_AFTER)
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all