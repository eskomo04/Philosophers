

NAME = philo

CFLAGS = -Wall -Werror -Wextra

SRCS = src/init.c src/utilis.c src/thread.c src/main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all	

.PHONY: all clean fclean re
