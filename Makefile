NAME	= cub3d

SRCS		= main.c initialize2.c file.c error.c free.c free2.c
SRCS		+= parse.c parse_first.c parse_second.c parse_second2.c parse_check.c
SRCS		+= draw2.c ray.c ray2.c view.c view2.c
SRCS    += utilities.c utilities2.c key.c
NORMAL  = draw.c initialize.c
BONUS		= minimap.c minimap2.c minimap3.c draw_bonus.c initialize_bonus.c
OBJS		= ${SRCS:.c=.o}
DEBUG_ARGS = -Wextra -Wall -fsanitize=address -fno-omit-frame-pointer -g3 -O3
CC_FLAGS := -Wextra -Wall -Werror

TESTS = debug.c
#OBJS_TESTS= ${TESTS:.c=.o}
#$(OBJS_TESTS): EXTRA_ARGS := -Wall -Wextra -fsanitize=address -g3 -O0

LIBS = -Llibft -LminilibX -lft -lmlx -lX11 -lXext -lm -lbsd

INCLUDES = -I.

all:	${NAME}

$(NAME):	${OBJS} ${NORMAL}
	make -C libft
	make -C minilibX
	gcc -o ${NAME} ${OBJS} ${NORMAL} ${INCLUDES} ${LIBS}

bonus:		${OBJS} ${BONUS}
	make -C libft
	make -C minilibX
	gcc -o ${NAME} ${OBJS} ${BONUS} ${INCLUDES} ${LIBS}

clean:
	rm -f *.gch
	make -C minilibX clean
	make -C libft clean
	rm -f ${OBJS}

tclean:		clean
	rm -f ${OBJS_TESTS}

fclean:		clean
	make -C minilibX clean
	make -C libft fclean
	rm -f ${NAME}

re:		fclean all

test: ${OBJS} ${OBJS_TESTS}
	make -C minilibX
	make -C libft
	gcc -o ./test ${OBJS} ${TESTS} ${INCLUDES} ${LIBS}

.c.o:
	gcc ${CC_FLAGS} -I. -c $< -o ${<:.c=.o}

.PHONY:	all clean fclean tclean re test bonus
