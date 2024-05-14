SRCS = ft_split.c test.c pipex.c
OBJS = ${SRCS:.c=.o}
NAME = pipex
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${SRCS} -o ${NAME}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}
