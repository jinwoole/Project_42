/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 18:58:31 by jinwoole          #+#    #+#             */
/*   Updated: 2022/02/08 14:14:57 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

char	*get_next_line(int fd);
char	*read_to_backup(int fd, char *backup_str);
char	*get_line(char *backup_str);
char	*new_backup_str(char *backup_str);
char	*ft_strchr_g(char *s, int c);
char	*ft_strjoin_g(char *s1, char *s2);
size_t	ft_strlen_g(char *s);

#endif
