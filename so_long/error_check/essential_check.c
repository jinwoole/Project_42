/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   essential_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:14:57 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 13:26:02 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static int	is_there_e(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'E')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_there_c(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'C')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	is_there_p(t_map *map)
{
	int	i;
	int	j;
	int	result;

	i = 0;
	result = 0;
	while (map->data[i])
	{
		j = 0;
		while (map->data[i][j])
		{
			if (map->data[i][j] == 'P')
				result++;
			j++;
		}
		i++;
	}
	return (result);
}

void	essential_check(t_map *map)
{
	if (is_there_e(map) == 0)
	{
		exit_error("No Exit? You are so mean", map);
	}
	if (is_there_c(map) == 0)
	{
		exit_error("No item? Are you kidding?", map);
	}
	if (is_there_p(map) == 0)
	{
		exit_error("No player? Don't you want to exist?", map);
	}
	if (is_there_p(map) > 1)
	{
		exit_error("More than 1 player? Are you kidding?", map);
	}
}
