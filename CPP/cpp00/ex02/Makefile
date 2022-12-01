# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 14:54:59 by jinwoole          #+#    #+#              #
#    Updated: 2022/09/04 10:28:37 by jinwoole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = revive
CC = c++

SRCS = test.cpp Account.cpp

all : $(NAME)

$(NAME): $(SRCS)
	$(CC) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

re:
	make clean
	make all

.PHONY: all clean re