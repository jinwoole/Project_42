/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:42:50 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/29 18:03:31 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	shape_check(char *path, t_map *map)
{
	int		fd;
	char	*line;
	int		length;
	int		height;

	fd = open(path, O_RDONLY);
	length = 0;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strlen(line) < 3)
			exit_error("map too narrow", map);
		if (length != 0 && (int)ft_strlen(line) != length)
			exit_error("Map data is not rectangle", map);
		length = ft_strlen(line);
		height++;
		free(line);
		line = get_next_line(fd);
	}
	if (height < 3)
		exit_error("Is this even a map file?", map);
	close(fd);
}
