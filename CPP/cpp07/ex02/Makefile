NAME = 02
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

all : $(NAME)

clean:
	rm -rf $(NAME)

re:
	make clean
	make all

.PHONY: all clean re