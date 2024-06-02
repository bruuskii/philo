SRCS = helpers.c init.c monitor.c routine.c philo.c
OBJS = ${SRCS:.c=.o}
NAME = philo
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g

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
