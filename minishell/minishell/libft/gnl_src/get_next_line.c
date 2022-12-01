/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesim <sesim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:53:34 by sesim             #+#    #+#             */
/*   Updated: 2022/07/11 16:03:47 by sesim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reader(int fd, char *bac)
{
	char	*buf;
	ssize_t	r_cnt;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	r_cnt = 1;
	while (!ft_strchr_g(bac, '\n') && r_cnt != 0)
	{
		r_cnt = read(fd, buf, BUFFER_SIZE);
		if (r_cnt == -1)
			break ;
		buf[r_cnt] = '\0';
		bac = ft_strjoin_g(bac, buf);
	}
	free(buf);
	buf = 0;
	return (bac);
}

char	*get_line(char *bac)
{
	char	*line;
	int		len;

	if (bac[0] == 0)
		return (0);
	if (ft_strchr_g(bac, '\n'))
		len = ft_strchr_g(bac, '\n') - bac + 2;
	else
		len = ft_strlen_g(bac) + 1;
	line = malloc(sizeof(char) * len);
	if (line == 0)
		return (0);
	ft_strlcpy_g(line, bac, len);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*bac;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bac = reader(fd, bac);
	if (bac == 0)
		return (0);
	res = get_line(bac);
	bac = new_line(bac);
	return (res);
}

/*
char	*get_file(int fd)
{
	char	*bac;
	char	buf[BUFFER_SIZE + 1];
	ssize_t	r_cnt;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	r_cnt = 1;
	while (r_cnt != 0)
	{
		r_cnt = read(fd, buf, BUFFER_SIZE);
		if (r_cnt == -1)
			break ;
		buf[r_cnt] = '\0';
		bac = ft_strjoin_g(bac, buf);
	}
	return (bac);
}

char	*reader(int fd, char *bac)
{
	char	*buf;
	ssize_t	r_cnt;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buf == 0)
		return (0);
	r_cnt = 1;
	while (r_cnt != 0)
	{
		r_cnt = read(fd, buf, BUFFER_SIZE);
		if (r_cnt == -1)
			break ;
		buf[r_cnt] = '\0';
		bac = ft_strjoin_g(bac, buf);
	}
	free(buf);
	buf = 0;
	return (bac);
}

char	*get_file(int fd)
{
	static char	*bac;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bac = reader(fd, bac);
	if (bac == 0)
		return (0);
	return (bac);
}
*/
