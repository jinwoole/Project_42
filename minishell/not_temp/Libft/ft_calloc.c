/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 11:54:34 by zcanales          #+#    #+#             */
/*   Updated: 2022/08/09 12:08:20 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr_s;

	ptr_s = malloc(size * nmemb);
	if (!ptr_s)
		return (NULL);
	ft_bzero(ptr_s, (nmemb * size));
	return (ptr_s);
}
