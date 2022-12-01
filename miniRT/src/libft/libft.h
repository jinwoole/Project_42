/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:47:05 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/08 10:43:58 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
void				ft_putstr(char const *s);
void				ft_putchar_fd(char c, int fd);
void				ft_puterror(char const *s);

#endif
