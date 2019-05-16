CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_itoa_base_u.c ft_memalloc.c ft_numlen.c \
ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strnew.c
OBJ = $(SRC:.c=.o)

PFSRC = ft_printf.c pf_parser.c pf_make_string.c pf_make_feg.c \
		pf_printer.c pf_support.c pf_support_feg.c
PFOBJ =  $(PFSRC:.c=.o)
PFDIR = ./printf/

.PHONY: all clean fclean re dep

all: $(NAME)

$(NAME): dep
	@$(CC) $(FLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ) $(PFOBJ)
	@ranlib $(NAME)

dep:
	@$(CC) $(FLAGS) -c $(patsubst %, $(PFDIR)%, $(PFSRC))

clean:
	@rm -f $(OBJ) $(PFOBJ)

fclean:	clean
	@rm -f $(NAME)

re: fclean all
