SRCS = events.c init.c math_utils.c render.c string_utils.c main.c
OBJS = ${SRCS:.c=.o}
NAME = fractol
CC = gcc
RM = rm -f
CFLAGS = -lmlx -lXext -lX11 -lm #-lmlx #-framework OpenGL #-framework AppKit

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${OBJS} -o ${NAME} ${CFLAGS}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}
