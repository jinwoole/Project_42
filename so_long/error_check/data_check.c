/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:31:17 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 13:27:37 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	guard_of_the_wall(t_map *map)
{
	int	i;

	i = 0;
	while (map->data[i])
	{
		if (map->data[i][0] != '1' || map->data[i][map->width - 1] != '1')
		{
			free(map->data);
			exit_error("the wall has to be well protected", map);
		}
		i++;
	}
}

static void	the_wall(t_map *map)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (map->data[i])
	{
		if (i == 0 || i == map->height - 1)
		{
			r = 0;
			while (r < map->width)
			{
				if (map->data[i][r] != '1')
				{
					free(map->data);
					exit_error("the wall has to be protected", map);
				}
				r++;
			}
		}
		i++;
	}
}

static void	evil_things(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] != '0' && map->data[i][j] != '1')
			{
				if (map->data[i][j] != 'E' && map->data[i][j] != 'C')
				{
					if (map->data[i][j] != 'P')
					{
						free(map->data);
						exit_error("In the name of iMac, go away Satan!", map);
					}
				}
			}
			j++;
		}
		i++;
	}
}

void	data_check(t_map *map)
{
	the_wall(map);
	guard_of_the_wall(map);
	evil_things(map);
	essential_check(map);
}
