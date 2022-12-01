# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/04 11:23:19 by sooyokim          #+#    #+#              #
#    Updated: 2022/11/08 10:31:56 by sooyokim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
HEADERS = includes

MLXDIR = miniLibX
LIBMLX = libmlx.dylib

SRC_DIR = src
LIBFT_DIR = src/libft
UTIL_DIR = src/utils
CTRL_DIR = src/control
PARSE_DIR = src/parsing
RENDER_DIR = src/render
PRINT_DIR = src/print
SCENE_DIR = src/scene
TRACE_DIR = src/trace
HIT_DIR = $(TRACE_DIR)/hit
RAY_DIR = $(TRACE_DIR)/ray

MLX_LNK = -L $(MLXDIR) -lmlx -framework OpenGL -framework AppKit -O3
LIBFT_LNK = -L $(LIBFT_DIR) -lft


SRCS = $(CTRL_DIR)/keyboard.c $(CTRL_DIR)/mouse.c $(CTRL_DIR)/zoom.c \
		$(CTRL_DIR)/move.c $(CTRL_DIR)/screen.c \
		$(RENDER_DIR)/render.c \
		$(UTIL_DIR)/terminate.c $(UTIL_DIR)/utils.c \
		$(UTIL_DIR)/object_utils.c \
		$(UTIL_DIR)/vec3_utils_1.c $(UTIL_DIR)/vec3_utils_2.c $(UTIL_DIR)/vec3_utils_3.c $(UTIL_DIR)/vec3_utils_4.c\
		$(PARSE_DIR)/initial_setting.c \
		$(PRINT_DIR)/print.c \
		$(SCENE_DIR)/canvas.c $(SCENE_DIR)/object_create.c $(SCENE_DIR)/scene.c \
		$(TRACE_DIR)/ray.c \
		$(HIT_DIR)/hit_sphere.c $(HIT_DIR)/hit_plane.c \
		$(HIT_DIR)/hit_cylinder.c $(HIT_DIR)/hit_cylinder2.c \
		$(HIT_DIR)/hit.c $(HIT_DIR)/normal.c \
		$(RAY_DIR)/phong_lighting.c \
		$(SRC_DIR)/main.c

OBJECTS = $(SRCS:.c=.o)

%o : %c
	$(MAKE) -C $(MLXDIR)
	cp $(MLXDIR)/$(LIBMLX) ./
	$(MAKE) all -C $(LIBFT_DIR)
	$(CC) -I $(MLXDIR) -I $(HEADERS) -I $(LIBFT_DIR) -c $< -o $@ -O3

$(NAME) : $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFT_LNK) $(MLX_LNK) 

all : $(NAME)

bonus : $(NAME)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLXDIR) clean
	rm -rf $(LIBMLX)
	rm -rf $(OBJECTS)

fclean :
	$(MAKE) -C $(LIBFT_DIR) fclean
	make clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re 