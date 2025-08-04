.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra  -Werror -MMD -MP -I$(LIBFT_DIR)includes -Iincludes 
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 


NAME = minishell
FILES = builtins/builtins_env \
		builtins/env_prepare_builtins \
		builtins/ft_echo \
		builtins/ft_exit \
		builtins/ft_unset \
		builtins/cd \
		builtins/cd_utils \
		builtins/ft_export \
		builtins/ft_export_utils \
		builtins/ctrl \
		builtins/ctrl_heredoc \
		exec/execve_builtins_childs \
		exec/execve_builtins_no_childs \
		exec/func_pipex \
		exec/pipex \
		exec/utils \
		parsing/parsing_quote/check_quote_command \
		parsing/parsing_quote/parsing_full_quote_end \
		parsing/parsing_quote/parsing_full_quote \
		parsing/parsing_quote/parsing_mixed_quotes_more \
		parsing/parsing_quote/parsing_quote \
		parsing/parsing_quote/parsing_mixed_quotes \
		parsing/tokenize/tokenized \
		parsing/tokenize/count_tokens \
		parsing/tokenize/retokenize \
		parsing/tokenize/tokenized_quote_pip_dollar \
		parsing/tokenize/tokenized_redirect_word \
		parsing/tokenize/retokenize_utils \
		parsing/tokenize/before_tokenize \
		parsing/expand/return_expand \
		parsing/expand/parsing_get_env \
		parsing/expand/parsing_get_env_quote \
		parsing/check_tokens \
		parsing/check_parsing \
		prepare-exec/cmds \
		prepare-exec/fd_infiles \
		prepare-exec/prepare_to_pipex \
		prepare-exec/fd \
		prepare-exec/check_here_doc \
		prepare-exec/check_here_doc_utils \
		prepare-exec/fd_childs \
		prepare-exec/fd_outfiles \
		prepare-exec/pipex_env \
		free/garbage_collector \
		free/garbage_utils \
		free/error_with_free \
		messages/messages_builtins \
		messages/messages_error \
		run/init_minishell \
		run/main_utils \
		main \

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
	mkdir -p $(OBJ_DIR)parsing/expand
	mkdir -p $(OBJ_DIR)parsing/parsing_quote
	mkdir -p $(OBJ_DIR)parsing/tokenize
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