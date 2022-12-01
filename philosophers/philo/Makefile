# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/21 22:20:36 by jinwoole          #+#    #+#              #
#    Updated: 2022/07/28 14:27:42 by jinwoole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
NAME		= philo
SOURCES 	=	philo.c \
				init_philo.c \
				util.c \
				routine.c \
				monitor.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o philo

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)
	$(RM) philo

re: fclean all

.PHONY: all clean fclean re