/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:30 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 14:21:34 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move(int x, int y, t_mlx *mlx, char option)
{
	double		moving_unit;
	t_viewpoint	*v;

	v = mlx->vp;
	moving_unit = v->zoom * MOVE;
	if (option == 'u')
		v->offy -= ((double)1 / W_HEIGHT) * moving_unit;
	if (option == 'd')
		v->offy += ((double)1 / W_HEIGHT) * moving_unit;
	if (option == 'l')
		v->offx -= ((double)1 / W_WIDTH) * moving_unit;
	if (option == 'r')
		v->offx += ((double)1 / W_WIDTH) * moving_unit;
	// render(mlx);
}
