/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:17:10 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 17:11:08 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./mlx/mlx.h"
# include <fcntl.h>
# include <stdlib.h>
# include "./get_next_line/get_next_line.h"
# include <stdio.h>

# define KEY_PRESS	2
# define KEY_EXIT	17
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

typedef struct s_map {
	void	*mlx;
	void	*mlx_win;
	int		height;
	int		width;
	int		collect;
	int		player_x;
	int		player_y;
	int		player_c;
	int		move;
	char	**data;
}				t_map;

void	map_info(char *path, t_map *map);
void	exit_error(char *str, t_map *map);
void	name_error(int argc, char **argv, t_map *map);
void	shape_check(char *path, t_map *map);
void	data_check(t_map *map);
void	essential_check(t_map *map);
int		exit_game(t_map *map);
int		press_key(int key, t_map *map);
void	render(t_map *map);
int		close_map(t_map *map);
void	move_w(t_map *map);
void	move_s(t_map *map);
void	move_a(t_map *map);
void	move_d(t_map *map);
void	num_render(t_map *map, int img_w, int img_h);
void	where_is_player(t_map *map);
void	how_many_c(t_map *map);

#endif