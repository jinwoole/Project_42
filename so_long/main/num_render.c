/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinwoole <indibooks@naver.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:02 by jinwoole          #+#    #+#             */
/*   Updated: 2022/05/31 17:14:24 by jinwoole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long_bonus.h"

char	*num_file(char number)
{
	if (number == '0')
		return ("./num/0.xpm");
	if (number == '1')
		return ("./num/1.xpm");
	if (number == '2')
		return ("./num/2.xpm");
	if (number == '3')
		return ("./num/3.xpm");
	if (number == '4')
		return ("./num/4.xpm");
	if (number == '5')
		return ("./num/5.xpm");
	if (number == '6')
		return ("./num/6.xpm");
	if (number == '7')
		return ("./num/7.xpm");
	if (number == '8')
		return ("./num/8.xpm");
	if (number == '9')
		return ("./num/9.xpm");
	return (0);
}

static int	itoa_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;

	i = itoa_len(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == 0)
		return (0);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
		str[0] = '-';
	while (n != 0)
	{
		if (str[0] == '-')
			str[i--] = '0' - (n % 10);
		else
			str[i--] = '0' + (n % 10);
		n = n / 10;
	}
	return (str);
}

void	num_render(t_map *map, int img_w, int img_h)
{
	void	*img;
	char	*num;
	char	*file;
	int		len;
	int		i;

	img = 0;
	i = 0;
	num = ft_itoa(map->move);
	len = ft_strlen(num);
	while (len - i > 0)
	{
		file = num_file(num[i]);
		img = mlx_xpm_file_to_image(map->mlx, file, &img_w, &img_h);
		mlx_put_image_to_window(map->mlx, map->mlx_win, img, 32 * i, 0);
		i++;
	}
	free(num);
}
