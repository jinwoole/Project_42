/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:03:42 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 13:33:03 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	map_read_check(int argc, char **argv, t_map *map)
{
	char	*map_path;

	map_path = argv[1];
	name_error(argc, argv, map);
	shape_check(map_path, map);
	map_info(map_path, map);
	data_check(map);
	where_is_player(map);
	how_many_c(map);
	map->move = 0;
	map->player_c = 0;
}

int	close_map(t_map *map)
{
	mlx_destroy_window(map->mlx, map->mlx_win);
	free(map->data);
	free(map);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		rw;
	int		rh;

	map = malloc(sizeof(t_map));
	map_read_check(argc, argv, map);
	rw = map->width * 64;
	rh = map->height * 64;
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, rw, rh, "so_long");
	render(map);
	mlx_hook(map->mlx_win, KEY_PRESS, 0, &press_key, map);
	mlx_hook(map->mlx_win, KEY_EXIT, 0, &close_map, map);
	mlx_loop(map->mlx);
}
