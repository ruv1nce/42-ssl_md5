CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = ft_ssl

SRC = main.c ssl_printer.c ssl_parser.c
OBJ = $(SRC:.c=.o)
LIB = ./libft/libft.a

.PHONY: all clean fclean re lib

all: $(NAME)

$(NAME): dep
	$(CC) $(FLAGS) $(SRC) $(LIB) -o $(NAME)

dep:
	$(MAKE) -C ./libft/

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft/ clean

fclean:	clean
	rm -f $(NAME)
	$(MAKE) -C ./libft/ fclean

re: fclean all
