.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra  -Werror -MMD -MP -I$(LIBFT_DIR)includes -Iincludes 
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 


NAME = minishell
FILES = builtins/builtins_env \
		builtins/cd \
		builtins/env_prepare_builtins \
		builtins/ft_echo \
		builtins/ft_exit \
		builtins/ft_export \
		builtins/ft_unset \
		builtins/cd_utils \
		builtins/ft_export_utils \
		exec/execve_builtins_childs \
		exec/execve_builtins_no_childs \
		exec/func_pipex \
		exec/pipex \
		exec/utils \
		parsing/ctrl_heredoc \
		parsing/retokenize \
		parsing/retokenize_final \
		parsing/check_quote_command \
		parsing/check_tokens \
		parsing/count_tokens \
		parsing/ctrl \
		parsing/parsing \
		parsing/parsing_full_quote \
		parsing/parsing_full_quote_end \
		parsing/parsing_get_env \
		parsing/parsing_get_env_quote \
		parsing/parsing_mixed_quotes \
		parsing/parsing_mixed_quotes_more \
		parsing/parsing_quote \
		parsing/pre_parsing \
		parsing/return_expand \
		parsing/tokenized \
		parsing/tokenized_more \
		parsing/tokenized_more2 \
		prepare-exec/cmds \
		prepare-exec/fd_infiles \
		prepare-exec/prepare_to_pipex \
		prepare-exec/fd \
		prepare-exec/check_here_doc \
		prepare-exec/check_here_doc_utils \
		prepare-exec/fd_childs \
		prepare-exec/fd_outfiles \
		prepare-exec/pipex_env \
		free/free \
		free/free_utils \
		free/error_and_free \
		messages/messages \
		messages/messages_utils \
		run/init_minishell \
		run/main \

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
	mkdir -p $(OBJ_DIR)parsing
	mkdir -p $(OBJ_DIR)exec
	mkdir -p $(OBJ_DIR)prepare-exec
	mkdir -p $(OBJ_DIR)builtins
	mkdir -p $(OBJ_DIR)free
	mkdir -p $(OBJ_DIR)messages
	mkdir -p $(OBJ_DIR)run
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