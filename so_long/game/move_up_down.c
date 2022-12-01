/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_up_down copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:10:49 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 17:08:44 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	move_protocol1(t_map *map, int from_x, int to_x, int y)
{
	if (map->data[to_x][y] == '0')
	{
		map->data[from_x][y] = '0';
		map->data[to_x][y] = 'P';
		map->player_x = to_x;
		map->move += 1;
		printf("%d\n", map->move);
	}
	else if (map->data[to_x][y] == 'C')
	{
		map->data[from_x][y] = '0';
		map->data[to_x][y] = 'P';
		map->player_x = to_x;
		map->player_c += 1;
		map->move += 1;
		printf("%d\n", map->move);
	}
	else if (map->data[to_x][y] == 'E')
	{
		if (map->player_c == map->collect)
			close_map(map);
	}
	render(map);
}

void	move_w(t_map *map)
{
	int	x;
	int	to_x;
	int	y;

	x = map->player_x;
	to_x = x - 1;
	y = map->player_y;
	move_protocol1(map, x, to_x, y);
}

void	move_s(t_map *map)
{
	int	x;
	int	to_x;
	int	y;

	x = map->player_x;
	to_x = x + 1;
	y = map->player_y;
	move_protocol1(map, x, to_x, y);
}
