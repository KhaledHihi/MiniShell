NAME = minishell

CFLAGS = -Wall -Wextra -Werror

SRC = main.c

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BNS_OBJ)
	@$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME) $(BNS_NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re

.SECONDARY : $(OBJ)
