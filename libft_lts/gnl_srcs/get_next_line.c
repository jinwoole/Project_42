/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:58:33 by jinwoole          #+#    #+#             */
/*   Updated: 2022/02/08 14:14:58 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_to_backup(int fd, char *backup_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == 0)
		return (0);
	rd_bytes = 1;
	while (!ft_strchr_g(backup_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (0);
		}
		buff[rd_bytes] = '\0';
		backup_str = ft_strjoin_g(backup_str, buff);
	}
	free(buff);
	return (backup_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	backup_str = read_to_backup(fd, backup_str);
	if (backup_str == 0)
		return (0);
	line = get_line(backup_str);
	backup_str = new_backup_str(backup_str);
	return (line);
}
