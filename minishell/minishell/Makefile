# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/08 21:26:07 by sesim             #+#    #+#              #
#    Updated: 2022/08/12 00:21:09 by sesim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

PWD = /opt/homebrew/opt/readline/
RFLAGS = -I $(PWD)/include \
		 -lreadline \
		 -L $(PWD)/lib

NAME = minishell

SRCS_DIR = ./srcs/

SRCS = $(SRCS_DIR)minishell.c \
	   $(SRCS_DIR)signal.c

OBJS = $(SRCS:.c=.o)

