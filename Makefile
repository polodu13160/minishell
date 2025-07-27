.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra   -MMD -MP -I$(LIBFT_DIR)includes -Iincludes -g3
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 


NAME = minishell
FILES = main \
		parsing/tokenized \
		parsing/tokenized_more \
		parsing/tokenized_more2 \
		parsing/count_tokens \
		builtins/ft_echo \
		parsing/pre_parsing \
		parsing/parsing_quote \
		parsing/parsing \
		parsing/parsing_get_env \
		parsing/parsing_full_quote \
		builtins/cd \
		prepare-exec/check_here_doc \
		exec/pipex \
		exec/func_pipex \
		error_and_free \
		messages \
		prepare-exec/cmds \
		prepare-exec/fd_childs \
		prepare-exec/fd_infiles \
		prepare-exec/fd_outfiles \
		prepare-exec/fd \
		prepare-exec/prepare_to_pipex \
		prepare-exec/pipex_env \
		builtins/cd2 \
		builtins/ft_exit \
		builtins/ft_export \
		builtins/ft_unset \
		builtins/builtins_env \
		free \
		parsing/ctrl \
		exec/execve_builtins_childs \
		parsing/check_tokens \
		builtins/env_prepare_builtins \
		init_minishell \
		free2 \
		exec/execve_builtins_no_childs \
		builtins/ft_export2 \
		parsing/retokenize \
		parsing/retokenize_final \
		parsing/check_quote_command \
		parsing/parsing_full_quote_end \
		parsing/parsing_get_env_quote \
		parsing/return_expand \
		prepare-exec/check_here_doc_signals \
		parsing/ctrl_heredoc \
		utils \
		builtins/ft_export_utils \
		messages2 \

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