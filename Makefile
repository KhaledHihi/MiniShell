NAME = minishell

CFLAGS = -Wall -Wextra -Werror -O2

SRC = main.c tokenize.c print_list.c init_env.c realoc.c prs_cmd.c garbage_collector.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJ)
	$(MAKE) -C libft
	$(MAKE) bonus -C libft
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

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
