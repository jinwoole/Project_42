/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_lr_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:10:49 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 17:14:08 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static void	move_protocol2(t_map *map, int x, int to_y, int y)
{
	if (map->data[x][to_y] == '0')
	{
		map->data[x][y] = '0';
		map->data[x][to_y] = 'P';
		map->player_y = to_y;
		map->move += 1;
	}
	else if (map->data[x][to_y] == 'C')
	{
		map->data[x][y] = '0';
		map->data[x][to_y] = 'P';
		map->player_y = to_y;
		map->player_c += 1;
		map->move += 1;
	}
	else if (map->data[x][to_y] == 'E')
	{
		if (map->player_c == map->collect)
			close_map(map);
	}
	render(map);
}

void	move_a(t_map *map)
{
	int	x;
	int	to_y;
	int	y;

	x = map->player_x;
	y = map->player_y;
	to_y = y - 1;
	move_protocol2(map, x, to_y, y);
}

void	move_d(t_map *map)
{
	int	x;
	int	to_y;
	int	y;

	x = map->player_x;
	y = map->player_y;
	to_y = y + 1;
	move_protocol2(map, x, to_y, y);
}
