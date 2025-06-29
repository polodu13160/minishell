.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra  -g3 -MMD -MP -I$(LIBFT_DIR)includes -Iincludes
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 

NAME = minishell
FILES = main \
		tokenized \
		tokenized_more \
		tokenized_more2 \
		count_tokens \
		ft_echo \
		pre_parsing \
		parsing_quote \
		parsing \
		parsing_get_env \
		parsing_full_quote \
		cd \
		check_here_doc \
		pipex \
		func_pipex \
		error_and_free \
		messages \
		cmds \
		fd_childs \
		fd_infiles \
		fd_outfiles \
		fd \
		prepare_to_pipex \
		pipex_env \
		cd2 \
		ft_exit \
		ft_export \
		ft_unset \
		builtins_env \
		free \
		ctrl \
		execve_builtins \
		check_tokens \
		env_prepare_builtins \
		init_minishell \
		free2 \
		execve_builtins_first \
		ft_export2 \
		retokenize \
		retokenize_final \
		check_quote_command \
		parsing_full_quote_end \
		parsing_get_env_quote \
		return_expand \

OBJ_DIR = objects/
SRC_DIR = sources/
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))
DEPS = $(addprefix $(OBJ_DIR), $(addsuffix .d, $(FILES)))

LIBFT_DIR = libft/
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