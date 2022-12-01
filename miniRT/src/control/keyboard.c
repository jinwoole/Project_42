/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:06 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 14:21:01 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "keys.h"
#include <stdlib.h>
#include "mlx.h"

void	color_change(int key, t_mlx *mlx)
{
	if (key == K_DIGIT_1)
		mlx->color_set = 0.3;
	if (key == K_DIGIT_2)
		mlx->color_set = 0.2;
	if (key == K_DIGIT_3)
		mlx->color_set = 0.4;
	if (key == K_DIGIT_4)
		mlx->color_set = 0.5;
	// render(mlx,);
}

int	hook_key(int key, t_mlx *mlx)
{
	if (key == K_ESC)
		terminate_fractol(mlx);
	if (key == K_NUM_0)
		reset_viewpoint(mlx);
	if (key == K_NUM_PLUS)
		zoom(W_WIDTH / 2, W_HEIGHT / 2, mlx, 1 / ZOOM);
	if (key == K_NUM_MINUS)
		zoom(W_WIDTH / 2, W_HEIGHT / 2, mlx, ZOOM);
	if (key == K_UP)
		move(0, 0, mlx, 'u');
	if (key == K_DOWN)
		move(0, 0, mlx, 'd');
	if (key == K_LEFT)
		move(0, 0, mlx, 'l');
	if (key == K_RIGHT)
		move(0, 0, mlx, 'r');
	if (18 <= key && key <= 21)
		color_change(key, mlx);
	return (0);
}
