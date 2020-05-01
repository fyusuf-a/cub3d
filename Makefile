NAME	= cub3d

SRCS		= main.c initialize.c file.c error.c 
SRCS		+= parse_first.c parse_second.c parse_check.c parse_utilities.c
OBJS		= ${SRCS:.c=.o}
DEBUG_ARGS = -Wextra -Wall -fsanitize=address -g3 -O0
$(OBJS): EXTRA_ARGS := -Werror -Wextra -Wall

TESTS = debug.c
#OBJS_TESTS= ${TESTS:.c=.o}
#$(OBJS_TESTS): EXTRA_ARGS := -Wall -Wextra -fsanitize=address -g3 -O0

LIBS = -Llibft -Lminilibx-linux -lft -lmlx -lX11 -lXext

INCLUDES = -I.

all:	${NAME}

$(NAME):	${OBJS}
	make -C libft
	gcc -o ${NAME} ${OBJS} ${INCLUDES} ${LIBS}

clean:
	rm -f *.gch
	make -C libft clean
	rm -f ${OBJS}

tclean:		clean
	rm -f ${OBJS_TESTS}

fclean:		clean
	make -C libft fclean
	rm -f ${NAME}

re:		fclean all

test: ${OBJS} ${OBJS_TESTS}
	make -C libft
	gcc -o ./test ${OBJS} ${TESTS} ${INCLUDES} ${LIBS}

.c.o:
	gcc ${EXTRA_ARGS} -I. -c $< -o ${<:.c=.o}

.PHONY:	all clean fclean tclean re test bonus libft
