NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC =	main.c \
		parsing/tokenize.c \
		parsing/print_list.c \
		parsing/init_env.c \
		parsing/realoc.c \
		parsing/prs_cmd.c \
		parsing/garbage_collector.c \
		parsing/expand_env.c \
		parsing/join_char.c \
		parsing/expand_cases.c \
		parsing/lst_tokenize.c \
		parsing/handle_token.c \

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
