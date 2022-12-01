/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:11 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 14:21:19 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	hook_mouse(int button, int x, int y, t_mlx *mlx)
{
	if (button == 4)
	{
		zoom(x, W_HEIGHT - y, mlx, 1 / ZOOM);
		// render(mlx);
	}
	else if (button == 5)
	{
		zoom(x, W_HEIGHT - y, mlx, ZOOM);
		// render(mlx);
	}
	return (0);
}
