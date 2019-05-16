CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = ft_ssl

SRC = main.c ssl_printer.c ssl_parser.c ssl_iterator.c ft_md5.c ft_sha256.c
OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

.PHONY: all clean fclean re lib

all: $(NAME)

$(NAME): dep
	@echo "rigging elections..."
	@$(CC) $(FLAGS) $(SRC) $(LIB) -o $(NAME)
	@echo "done"

dep:
	@echo "hacking penthagon mainframe..."
	@$(MAKE) -C ./libft/

clean:
	@echo "taking care of eywitnesses..."
	@rm -f $(OBJ)
	@$(MAKE) -C ./libft/ clean

fclean:	clean
	@echo "buying off judges..."
	@rm -f $(NAME)
	@$(MAKE) -C ./libft/ fclean

re: fclean all
