NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC = main.c tokenize.c print_list.c init_env.c 

OBJ = $(SRC:.c=.o)

libft = libft/libft.a

$(NAME): $(OBJ)
	@$(MAKE) -C libft
	$(CC) $(CFLAGS) $(OBJ) $(libft) -o $(NAME) -lreadline

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY : $(OBJ)
