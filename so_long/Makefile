# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 18:06:20 by jinwoole          #+#    #+#              #
#    Updated: 2022/05/31 17:13:11 by jinwoole         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME= so_long
MLX= libmlx.a

SOURCES =	main/main.c \
			main/read_map.c \
			main/render.c \
			error_check/name_check.c \
			error_check/shape_check.c \
			error_check/data_check.c \
			error_check/essential_check.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			game/key.c \
			game/move_up_down.c \
			game/move_lr.c

SRC_BNS =	main/main_bonus.c \
			main/read_map.c \
			main/render_bonus.c \
			main/num_render.c\
			error_check/name_check.c \
			error_check/shape_check.c \
			error_check/data_check.c \
			error_check/essential_check.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c \
			game/key.c \
			game/move_up_down_bonus.c \
			game/move_lr_bonus.c

OBJECTS = $(SOURCES:.c=.o)
OBJ_BNS = $(SRC_BNS:.c=.o)

ifdef WITH_BONUS
	OBJ_FILES = $(OBJ_BNS)
else
	OBJ_FILES = $(OBJECTS)
endif

all: $(NAME)

$(NAME): $(MLX) $(OBJ_FILES)
	$(CC) $(CFLAGS) -L. -lmlx -framework OpenGl -framework Appkit $(OBJ_FILES) -o so_long

$(MLX):
	make -C ./mlx
	cp ./mlx/libmlx.a .

bonus:
	make WITH_BONUS=1 all

clean:
	$(RM) $(OBJECTS) $(OBJ_BNS)
	make clean -C ./mlx

fclean: clean
	$(RM) $(NAME)
	$(RM) $(MLX)
	$(RM) ./mlx/libmlx.a

re: fclean all

.PHONY: all clean fclean re bonus