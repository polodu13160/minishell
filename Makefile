.PHONY= all clean re fclean FORCE

CC = cc 
CFLAGS = -Wall -Wextra  -MMD -MP -I$(LIBFT_DIR)includes -Iincludes 
CFLAGS_AFTER = -lft -lreadline -o $(NAME) 


NAME = minishell
FILES =  builtins/cd \
       builtins/cd_utils \
       builtins/env_prepare_builtins \
       builtins/ft_echo \
       builtins/ft_export \
       builtins/ft_export_utils \
       builtins/ft_unset \
       builtins/builtins_env \
       builtins/ft_exit \
       exec/exec_in_child/execve_first \
       exec/exec_in_child/execve_last \
       exec/exec_in_child_builtins/execve_builtins_childs_last \
       exec/exec_in_child_builtins/execve_buitlins_childs_first \
       exec/exec_no_child_bultins/execve_builtins_no_childs \
       exec/pipex/pipex \
       exec/pipex/utils \
       exec/pipex/pipex_env \
       exec/management_fd_exec/check_perm_infiles_outfiles_in_child \
       exec/management_fd_exec/close_fd \
       exec/management_fd_exec/dup_and_close_in_child \
       exec/management_fd_exec/error_dup_fork_pipe_childs \
       parsing/expand/parsing_get_env_quote \
       parsing/expand/parsing_get_env \
       parsing/expand/return_expand \
       parsing/parsing_quote/parsing_mixed_quotes_more \
       parsing/parsing_quote/check_quote_command \
       parsing/parsing_quote/parsing_full_quote \
       parsing/parsing_quote/parsing_full_quote_end \
       parsing/parsing_quote/parsing_mixed_quotes \
       parsing/parsing_quote/parsing_quote \
       parsing/tokenize/count_tokens \
       parsing/tokenize/retokenize_utils \
       parsing/tokenize/check_is_retokenizable \
       parsing/tokenize/before_tokenize \
       parsing/tokenize/tokenized_quote_pip_dollar \
       parsing/tokenize/tokenized_redirect_word \
       parsing/tokenize/retokenize \
       parsing/tokenize/tokenized \
       parsing/validate_tokens_utils \
       parsing/validate_tokens \
       parsing/validate_parsing \
       parsing/validate_parsing_utils \
       prepare-exec/here_doc/check_here_doc_utils \
       prepare-exec/here_doc/check_here_doc \
       prepare-exec/from_parsing_to_exec/cmds \
       prepare-exec/from_parsing_to_exec/store_outfiles \
       prepare-exec/from_parsing_to_exec/store_infiles \
       prepare-exec/from_parsing_to_exec/prepare_to_pipex \
       run/init_minishell \
       run/run_minishell \
       free/error_with_free \
       free/garbage_collector \
       free/garbage_utils \
       messages/messages_builtins \
       messages/messages_error \
       main \
       signals/ctrl \
       signals/ctrl_heredoc \

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
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)parsing
	@mkdir -p $(OBJ_DIR)parsing/expand
	@mkdir -p $(OBJ_DIR)parsing/parsing_quote
	@mkdir -p $(OBJ_DIR)parsing/validate_tokens
	@mkdir -p $(OBJ_DIR)parsing/tokenize
	@mkdir -p $(OBJ_DIR)signals
	@mkdir -p $(OBJ_DIR)exec
	@mkdir -p $(OBJ_DIR)exec/exec_in_child
	@mkdir -p $(OBJ_DIR)exec/exec_in_child_builtins
	@mkdir -p $(OBJ_DIR)exec/exec_in_child_builtins
	@mkdir -p $(OBJ_DIR)exec/exec_no_child
	@mkdir -p $(OBJ_DIR)exec/exec_no_child_bultins
	@mkdir -p $(OBJ_DIR)exec/management_fd_exec
	@mkdir -p $(OBJ_DIR)exec/pipex
	@mkdir -p $(OBJ_DIR)prepare-exec
	@mkdir -p $(OBJ_DIR)prepare-exec/from_parsing_to_exec
	@mkdir -p $(OBJ_DIR)prepare-exec/here_doc
	@mkdir -p $(OBJ_DIR)builtins
	@mkdir -p $(OBJ_DIR)free
	@mkdir -p $(OBJ_DIR)messages
	@mkdir -p $(OBJ_DIR)run
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