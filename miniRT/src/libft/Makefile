# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooyokim <sooyokim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/14 13:53:42 by sooyokim          #+#    #+#              #
#    Updated: 2022/07/14 11:36:19 by sooyokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a
CC = cc
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_strlen.c ft_strcmp.c ft_putstr.c

SRCS = $(SRC)
OBJECTS = $(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJECTS)
	ar -rc $@ $^

bonus:
	@make WITH_BONUS=1 all

%.o:		%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJECTS)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

.PHONY:		all bonus clean fclean re