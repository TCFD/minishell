GREEN=\033[0;32m
NC=\033[0m

NAME = libft.a
FLAGS = -Wall -Wextra -Werror -g3
CC = ggcc

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
COMPILED := 0

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all
