/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:50:38 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 17:14:33 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

static char	*file_selector(t_map *map, int i, int j)
{
	if (map->data[i][j] == '0')
		return ("./src/0.xpm");
	else if (map->data[i][j] == '1')
		return ("./src/1.xpm");
	else if (map->data[i][j] == 'E')
		return ("./src/E.xpm");
	else if (map->data[i][j] == 'P')
		return ("./src/P.xpm");
	else if (map->data[i][j] == 'C')
		return ("./src/C.xpm");
	return (0);
}

static void	real_render(t_map *map, int i, int img_w, int img_h)
{
	void	*m;
	int		j;
	char	*f;

	j = 0;
	m = 0;
	while (i < map->height)
	{
		while (j < map->width)
		{
			f = file_selector(map, i, j);
			m = mlx_xpm_file_to_image(map->mlx, f, &img_w, &img_h);
			mlx_put_image_to_window(map->mlx, map->mlx_win, m, j * 64, i * 64);
			j++;
		}
		j = 0;
		i++;
	}
}

void	render(t_map *map)
{
	int	i;
	int	img_w;
	int	img_h;

	i = 0;
	img_w = 0;
	img_h = 0;
	real_render(map, i, img_w, img_h);
	num_render(map, img_w, img_h);
}
