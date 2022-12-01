# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:14:05 by jinwoole          #+#    #+#              #
#    Updated: 2022/06/23 14:23:14 by jinwoole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT_SRC			=	client.c \
						utils/ft_atoi_isdigit.c \
						utils/lenput.c
CLIENT_BONUS_SRC	=	client_bonus.c \
						utils/ft_atoi_isdigit.c \
						utils/lenput.c
SERVER_SRC			=	server.c \
						utils/ft_atoi_isdigit.c \
						utils/lenput.c	
SERVER_BONUS_SRC	=	server_bonus.c \
						utils/ft_atoi_isdigit.c \
						utils/lenput.c	

CLIENT_OBJ			= $(CLIENT_SRC:%.c=%.o)
CLIENT_BONUS_OBJ	= $(CLIENT_BONUS_SRC:%.c=%.o)
SERVER_OBJ			= $(SERVER_SRC:%.c=%.o)
SERVER_BONUS_OBJ	= $(SERVER_BONUS_SRC:%.c=%.o)

NAME	= server client
RM	= rm -f
CC	= gcc
CFLAGS = -Wall -Werror -Wextra

ifdef WITH_BONUS
	C_OBJ = $(CLIENT_BONUS_OBJ)
	S_OBJ = $(SERVER_BONUS_OBJ)
else
	C_OBJ = $(CLIENT_OBJ)
	S_OBJ = $(SERVER_OBJ)
endif

all: $(NAME)

$(NAME): $(S_OBJ) $(C_OBJ)
	$(CC) $(CFLAGS) $(S_OBJ) -o server
	$(CC) $(CFLAGS) $(C_OBJ) -o client

bonus:
	make WITH_BONUS=1 all

clean:
	$(RM) $(CLIENT_OBJ) $(CLIENT_BONUS_OBJ) $(SERVER_OBJ) $(SERVER_BONUS_OBJ)

fclean: clean
	$(RM) client
	$(RM) server

re: fclean all

.PHONY: all bonus clean fclean re rebonus