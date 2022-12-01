/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:39:17 by jinwoole          #+#    #+#             */
/*   Updated: 2021/12/15 16:19:03 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst1;
	unsigned char	*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	if (src < dst)
	{
		src1 = src1 + len - 1;
		dst1 = dst1 + len - 1;
		while (len--)
			*dst1-- = *src1--;
	}
	else if (src >= dst)
	{
		while (len--)
			*dst1++ = *src1++;
	}
	return (dst);
}
