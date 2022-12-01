/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:41 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 14:21:37 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"

t_complex	screen_to_complex(int count_x, int count_y, t_viewpoint *vp)
{
	t_complex	c;

	c.re = ((double)count_x / W_WIDTH * (vp->xmax - vp->xmin)) * \
							vp->zoom + vp->xmin + vp->offx;
	c.im = ((double)count_y / W_HEIGHT * (vp->ymax - vp->ymin)) * \
							vp->zoom + vp->ymin + vp->offy;
	return (c);
}

t_viewpoint	*init_viewpoint(t_viewpoint *vp)
{
	vp->offx = 0.0;
	vp->offy = 0.0;
	vp->xmax = -2.0;
	vp->xmin = 2.0;
	vp->ymax = 1.0;
	vp->ymin = -1.0;
	vp->zoom = 1.0;
	return (vp);
}

// void	viewpoint_setting(t_viewpoint *vp, const char *fractol)
// {
// 	if (ft_strcmp(fractol, "mandelbrot"))
// 		mandelbrot_viewpoint(vp);
// 	if (ft_strcmp(fractol, "julia"))
// 		julia_viewpoint(vp);
// 	if (ft_strcmp(fractol, "burningship"))
// 		burningship_viewpoint(vp);
// }

void	reset_viewpoint(t_mlx *mlx)
{
	init_viewpoint(mlx->vp);
	// viewpoint_setting(mlx->vp, mlx->fractol);
	// render(mlx);
}
