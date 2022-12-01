/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:29:36 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/07 19:45:43 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "mlx.h"
#include <math.h>
#include "structures.h"
#include "utils.h"
#include "print.h"
#include "scene.h"
#include "trace.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = (img->data) + (x * img->bpp / 8) + (y * img->size_l);
	*(unsigned int *)dst = color;
}

int	color_set(int iter, t_color3 pixel_color)
{
	double	r;
	double	g;
	double	b;
	int		color;

	// r = sin(color_set * (double)iter);
	// g = sin(color_set * (double)iter + 3) * 127 + 128;
	// b = sin(color_set * (double)iter + 3) * 127 + 128;
	// color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) \
	// 									+ ((int)(255.999 * b));

	r = (255.999 * pixel_color.x);
	g = (255.999 * pixel_color.y);
	b = (255.999 * pixel_color.z);
	// r = sin(pixel_color.x);
	// g = sin(pixel_color.y) * 127 + 128;
	// b = sin(pixel_color.z) * 127 + 128;
	// color = ((int)(255.999 * r) << 16) + ((int)(255.999 * g) << 8) \
	// 								+ ((int)(255.999 * b));
	color = ((int)(r) << 16) + ((int)(g) << 8) + ((int)(b));
	return (color);
}

// int	fractol_select(t_count c, int iter, t_mlx *mlx)
// {
// 	if (ft_strcmp(mlx->fractol, "mandelbrot"))
// 		iter = mandelbrot(c, 0, mlx->vp);
// 	if (ft_strcmp(mlx->fractol, "julia"))
// 		iter = julia(c, 0, mlx->vp, mlx->julia_c);
// 	if (ft_strcmp(mlx->fractol, "burningship"))
// 		iter = burningship(c, 0, mlx->vp);
// 	return (iter);
// }

void	render(t_mlx *mlx, t_scene *scene)
{
	t_img	img;
	int		iter;
	int		color;
	int i;
	int j;
	double      u;
    double      v;
	t_color3    pixel_color;

	i = -1;
	img = mlx->img;
	// iter = 0;
	
	while (++i < scene->canvas.width)
	{
		j = -1;
		while (++j < scene->canvas.height)
		{
			// printf("%d\n", j);
			u = (double)i / (scene->canvas.width - 1);
            v = (double)(scene->canvas.height - j) / (scene->canvas.height - 1);
            //ray from camera origin to pixel
            scene->ray = ray_primary(&scene->camera, u, v);
            pixel_color = ray_color(scene);
			color = color_set(iter, pixel_color);
			my_mlx_pixel_put(&img, i, j, color);
			// iter = fractol_select(c, 0, mlx);
			// if (iter < ITER_MAX)
			// {
			// 	color = color_set(iter, mlx->color_set);
			// 	my_mlx_pixel_put(&img, c.i, c.j, color);
			// }
			// else
			// 	my_mlx_pixel_put(&img, c.i, c.j, 0x00000000);
		}		
	}
	
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
								(mlx->img.img_ptr), 0, 0);
}


// void	render(t_mlx *mlx, t_scene *scene)
// {
// 	t_img	img;
// 	int		iter;
// 	int		color;
// 	t_count	c;

// 	c.i = -1;
// 	img = mlx->img;
// 	iter = 0;
// 	while (++c.i < W_WIDTH)
// 	{
// 		c.j = -1;
// 		while (++c.j < W_HEIGHT)
// 		{
// 			// iter = fractol_select(c, 0, mlx);
// 			if (iter < ITER_MAX)
// 			{
// 				color = color_set(iter, mlx->color_set);
// 				my_mlx_pixel_put(&img, c.i, c.j, color);
// 			}
// 			else
// 				my_mlx_pixel_put(&img, c.i, c.j, 0x00000000);
// 		}		
// 	}
// 	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
// 								(mlx->img.img_ptr), 0, 0);
// }
