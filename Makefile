NAME	= cub3d

SRCS		= main.c initialize2.c file.c error.c free.c free2.c
SRCS		+= parse.c parse_first.c parse_second.c parse_second2.c parse_check.c
SRCS		+= movement2.c ray.c ray2.c view.c view2.c
SRCS    += utilities.c utilities2.c key.c bmp.c
NORMAL  = movement.c draw.c initialize.c
BONUS   = movement_bonus.c draw_bonus.c initialize_bonus.c
BONUS		+= minimap_bonus.c minimap2_bonus.c minimap3_bonus.c draw2_bonus.c
OBJS		= ${SRCS:.c=.o}
DEBUG_ARGS = -Wextra -Wall -fsanitize=address -fno-omit-frame-pointer -g3

CC	 = clang 
CC_FLAGS = -Wextra -Wall -Werror

UNAME_S = $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	MINILIBX = minilibx-linux
else
ifeq ($(UNAME_S), Darwin)
	MINILIBX = minilibx-mac
else
$(error OS not supported)
endif
endif

LIBS = -Llibft -L${MINILIBX} -lft -lmlx -lX11 -lXext -lm -lbsd

INCLUDES = -I.


all:	${NAME}

$(NAME):	${OBJS} ${NORMAL}
	make -C libft
	make -C ${MINILIBX}
	${CC} -o ${NAME} ${OBJS} ${NORMAL} ${INCLUDES} ${LIBS}

bonus:		${OBJS} ${BONUS}
	make -C libft
	make -C ${MINILIBX}
	${CC} -o ${NAME} ${OBJS} ${BONUS} ${INCLUDES} ${LIBS}

clean:
	rm -f *.gch
	make -C ${MINILIBX} clean
	make -C libft clean
	rm -f ${OBJS}

tclean:		clean
	rm -f ${OBJS_TESTS}

fclean:		clean
	make -C ${MINILIBX} clean
	make -C libft fclean
	rm -f ${NAME}

re:		fclean all

test: ${OBJS} ${OBJS_TESTS}
	make -C minilibX
	make -C libft
	${CC} -o ./test ${OBJS} ${TESTS} ${INCLUDES} ${LIBS}

.c.o:
	${CC} ${CC_FLAGS} -I. -c $< -o ${<:.c=.o}

.PHONY:	all clean fclean tclean re test bonus
