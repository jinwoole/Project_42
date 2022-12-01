# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/26 14:54:47 by jinwoole          #+#    #+#              #
#    Updated: 2022/08/26 14:56:13 by jinwoole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = megaphone
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = megaphone.cpp

$(NAME): $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(NAME)

all : $(NAME)

clean:
	rm -rf $(NAME)

re:
	make clean
	make all

.PHONY: all clean re