/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:58:33 by jinwoole          #+#    #+#             */
/*   Updated: 2022/01/17 20:45:51 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
//#include <stdio.h>
//#include <fcntl.h>

char	*read_to_backup(int fd, char *backup_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == 0)
		return (0);
	rd_bytes = 1;
	while (!ft_strchr(backup_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (0);
		}
		buff[rd_bytes] = '\0';
		backup_str = ft_strjoin(backup_str, buff);
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

/* stdin 테스트 redr 1
int main(int ac, char **av) {
        int fd = 0;

        if (ac >= 2) {
                fd = open(av[1], O_RDONLY);
        }
        char *line = 0;
        while (1)
		{
        		line = get_next_line(0);
                printf("%s", line);
        }
}
*/

/* 파일 테스트
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("tests/test.txt", O_RDONLY);

	i = 0;
	while (i < 12)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}
*/