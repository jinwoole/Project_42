NAME = animal
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address

SRCS = main.cpp Animal.cpp Dog.cpp Cat.cpp Brain.cpp

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

all : $(NAME)

clean:
	rm -rf $(NAME)

re:
	make clean
	make all

.PHONY: all clean re