NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS_DIR = ./

SRCS =	$(SRCS_DIR)Builtins/cd_builtin.c \
		$(SRCS_DIR)Builtins/cd_utils.c \
		$(SRCS_DIR)Builtins/echo_builtin.c \
		$(SRCS_DIR)Builtins/env_builtin.c \
		$(SRCS_DIR)Builtins/execute_builtin.c \
		$(SRCS_DIR)Builtins/exit_builtin.c \
		$(SRCS_DIR)Builtins/export_builtin.c \
		$(SRCS_DIR)Builtins/pwd_builtin.c \
		$(SRCS_DIR)Builtins/unset_builtin.c \
		$(SRCS_DIR)Builtins/utils_builtin.c \
		$(SRCS_DIR)Environnements/env_management.c \
		$(SRCS_DIR)Environnements/env_initialization.c \
		$(SRCS_DIR)Environnements/env_conversion.c \
		$(SRCS_DIR)Redirections/input_redirections.c \
		$(SRCS_DIR)Redirections/output_redirections.c \
		$(SRCS_DIR)Redirections/redirection_execution.c \
		$(SRCS_DIR)Signal/signal_management.c \
		$(SRCS_DIR)Signal/heredoc_signals.c \
		$(SRCS_DIR)Signal/heredoc_utils.c \
		$(SRCS_DIR)Signal/signal_utils.c \
		$(SRCS_DIR)Parsing/parsing.c \
		$(SRCS_DIR)Parsing/tokenization.c \
		$(SRCS_DIR)Parsing/token_utils.c \
		$(SRCS_DIR)Parsing/quotes.c \
		$(SRCS_DIR)Parsing/quote_processing.c \
		$(SRCS_DIR)Parsing/expansion.c \
		$(SRCS_DIR)Parsing/expansion_utils.c \
		$(SRCS_DIR)Parsing/expansion_helpers.c \
		$(SRCS_DIR)Parsing/expansion_advanced.c \
		$(SRCS_DIR)Parsing/expansion_variable.c \
		$(SRCS_DIR)Parsing/syntax_check.c \
		$(SRCS_DIR)Parsing/syntax_utils.c \
		$(SRCS_DIR)Parsing/memory.c \
		$(SRCS_DIR)Parsing/command_utils.c \
		$(SRCS_DIR)Parsing/command_parsing.c \
		$(SRCS_DIR)Parsing/command_processing.c \
		$(SRCS_DIR)Parsing/redirection_utils.c \
		$(SRCS_DIR)Parsing/redirection_helpers.c \
		$(SRCS_DIR)Parsing/command_list_utils.c \
		$(SRCS_DIR)Execution/execution.c \
		$(SRCS_DIR)Execution/pipeline.c \
		$(SRCS_DIR)Execution/redirections.c \
		$(SRCS_DIR)Execution/heredoc.c \
		$(SRCS_DIR)Execution/child_process.c \
		$(SRCS_DIR)Execution/error_handling.c \
		$(SRCS_DIR)Execution/utils.c \
		$(SRCS_DIR)Execution/pipe_utils.c \
		$(SRCS_DIR)Execution/env_utils.c \
		$(SRCS_DIR)Execution/signal_utils.c \
		$(SRCS_DIR)utils/path_operations.c \
		$(SRCS_DIR)utils/path_utilities.c \
		$(SRCS_DIR)utils/parsing_utilities.c \
		$(SRCS_DIR)Debug/print_token.c \
		$(SRCS_DIR)main_utils.c \
		$(SRCS_DIR)main.c \


OBJS = $(SRCS:.c=.o)

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a
GET_NEXT_LINE_DIR = $(LIBFT_DIR)/get_next_line
GET_NEXT_LINE = $(GET_NEXT_LINE_DIR)/libftgetnextline.a

READLINE_INC = -I/usr/include
READLINE_LIB = -lreadline -L/usr/lib

INCLUDES = -I$(LIBFT_DIR) -I$(GET_NEXT_LINE_DIR) -Iincludes $(READLINE_INC)

all: $(LIBFT) $(GET_NEXT_LINE) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GET_NEXT_LINE):
	make -C $(GET_NEXT_LINE_DIR)

$(NAME): $(OBJS) $(LIBFT) $(GET_NEXT_LINE)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GET_NEXT_LINE) $(READLINE_LIB) -o $(NAME)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(GET_NEXT_LINE_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(GET_NEXT_LINE_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
