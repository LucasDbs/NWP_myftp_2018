##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Lucas Duboisse
##

NAME	=	myftp

SRC	=	src/server.c		\
		src/management.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-g -W -Wall -Wextra -Iinclude/

all:		$(NAME)

$(NAME):
		gcc -o $(NAME) $(SRC) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all