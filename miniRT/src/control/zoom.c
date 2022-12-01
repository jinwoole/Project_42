/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:46 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 14:21:25 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	zoom(int x, int y, t_mlx *mlx, double z)
{
	double		pre_w;
	double		pre_h;
	double		current_w;
	double		current_h;
	t_viewpoint	*v;

	v = mlx->vp;
	pre_w = (v->xmax - v->xmin) * (v->zoom);
	pre_h = (v->ymax - v->ymin) * (v->zoom);
	current_w = (v->xmax - v->xmin) * (v->zoom * z);
	current_h = (v->ymax - v->ymin) * (v->zoom * z);
	v->zoom *= z;
	v->offx -= ((double)x / W_WIDTH) * (current_w - pre_w);
	v->offy -= ((double)y / W_HEIGHT) * (current_h - pre_h);
	// render(mlx);
}
