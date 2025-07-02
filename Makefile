NAME = minishell

CFLAGS = -Wall -Wextra -Werror -fsanitize=address 

SRC =	main.c \
		parsing/tokenize.c \
		parsing/print_list.c \
		parsing/init_env.c \
		parsing/realloc.c \
		parsing/prs_cmd.c \
		parsing/parsing_utils.c \
		parsing/garbage_collector.c \
		parsing/expand_env.c \
		parsing/join_char.c \
		parsing/expand_cases.c \
		parsing/lst_tokenize.c \
		parsing/custom_errors.c \
		parsing/heredoc.c \
		parsing/heredoc_utils.c \
		partie-dexecution/execution_pipe.c \
		partie-dexecution/pipes_utils.c \
		partie-dexecution/redirection_in_et_out.c \
		partie-dexecution/redirection_in_et_out_utils.c \
		partie-dexecution/run_builtin.c \
		partie-dexecution/run_execution.c \
		partie-dexecution/run_extern_cmds.c \
		partie-dexecution/signales_herdoc.c \
		partie-dexecution/signals.c \
		partie-dexecution/utils.c \
		partie-dexecution/builtins/builtin_cd.c \
		partie-dexecution/builtins/builtin_echo.c \
		partie-dexecution/builtins/builtin_env.c \
		partie-dexecution/builtins/builtin_exit.c \
		partie-dexecution/builtins/builtin_export.c \
		partie-dexecution/builtins/builtin_pwd.c \
		partie-dexecution/builtins/builtin_unset.c \
		partie-dexecution/builtins/export_utils_1.c \
		partie-dexecution/builtins/export_utils_2.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(MAKE) bonus -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline
	$(MAKE) clean

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

debug: CFLAGS += -g
debug: re

.PHONY: all clean fclean re debug

.SECONDARY : $(OBJ)
