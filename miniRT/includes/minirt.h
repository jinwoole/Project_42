/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:32:00 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/04 15:06:56 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include "structures.h"

# define W_WIDTH 800
# define W_HEIGHT 600
# define ITER_MAX 100
# define ZOOM 1.5
# define MOVE 200.0


typedef struct structure_img{
	void		*img_ptr;
	char		*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct viewpoint_structure
{
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	zoom;
	double	offx;
	double	offy;
}			t_viewpoint;

typedef struct s_complex
{
	double		re;
	double		im;
}				t_complex;

typedef struct structure_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_viewpoint	*vp;
	double		color_set;
}				t_mlx;

typedef struct count_x_y
{
	int		i;
	int		j;
}	t_count;

int			hook_key(int key, t_mlx *mlx);
int			hook_mouse(int button, int x, int y, t_mlx *mlx);
void		zoom(int x, int y, t_mlx *mlx, double z);
void		render(t_mlx *mlx, t_scene *scene);
void		move(int x, int y, t_mlx *mlx, char option);
t_complex	screen_to_complex(int count_x, int count_y, t_viewpoint *vp);
int			input_check(int ac, const char **av);
t_mlx		*mlx_structure_init(t_mlx *mlx, t_scene *scene);
t_viewpoint	*init_viewpoint(t_viewpoint *vp);
t_mlx		*init_mlx(const char *fractol, const char **av, t_scene *scene);
t_img		new_image(t_mlx *mlx, t_scene *scene);
// int			mandelbrot(t_count count, int iter, t_viewpoint *vp);
// int			julia(t_count count, int iter, t_viewpoint *vp, t_complex c);
// int			burningship(t_count count, int iter, t_viewpoint *v);
void		viewpoint_setting(t_viewpoint *vp, const char *f);
// void		mandelbrot_viewpoint(t_viewpoint *vp);
// void		julia_viewpoint(t_viewpoint *v);
// void		burningship_viewpoint(t_viewpoint *v);
double		atod_check(char *str, int *error);

int			terminate_fractol(t_mlx *mlx);
void		reset_viewpoint(t_mlx *mlx);
int			error_return_zero(int *error);

#endif



// #ifndef MINIRT_H
// # define MINIRT_H

// # include <stdlib.h>

// # define W_WIDTH 800
// # define W_HEIGHT 600
// # define ITER_MAX 100
// # define ZOOM 1.5
// # define MOVE 200.0

// typedef struct structure_img{
// 	void		*img_ptr;
// 	char		*data;
// 	int			size_l;
// 	int			bpp;
// 	int			endian;
// }				t_img;

// typedef struct viewpoint_structure
// {
// 	double	xmin;
// 	double	xmax;
// 	double	ymin;
// 	double	ymax;
// 	double	zoom;
// 	double	offx;
// 	double	offy;
// }			t_viewpoint;

// typedef struct s_complex
// {
// 	double		re;
// 	double		im;
// }				t_complex;

// typedef struct structure_mlx
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_img		img;
// 	t_viewpoint	*vp;
// 	const char	*fractol;
// 	t_complex	julia_c;
// 	double		color_set;
// }				t_mlx;

// typedef struct count_x_y
// {
// 	int		i;
// 	int		j;
// }	t_count;

// int			hook_key(int key, t_mlx *mlx);
// int			hook_mouse(int button, int x, int y, t_mlx *mlx);
// void		zoom(int x, int y, t_mlx *mlx, double z);
// void		render(t_mlx *mlx);
// void		move(int x, int y, t_mlx *mlx, char option);
// t_complex	screen_to_complex(int count_x, int count_y, t_viewpoint *vp);
// int			input_check(int ac, const char **av);
// t_mlx		*mlx_structure_init(t_mlx *mlx);
// t_viewpoint	*init_viewpoint(t_viewpoint *vp);
// t_mlx		*init_mlx(const char *fractol, const char **av);
// t_img		new_image(t_mlx *mlx);
// int			mandelbrot(t_count count, int iter, t_viewpoint *vp);
// int			julia(t_count count, int iter, t_viewpoint *vp, t_complex c);
// int			burningship(t_count count, int iter, t_viewpoint *v);
// void		viewpoint_setting(t_viewpoint *vp, const char *f);
// void		mandelbrot_viewpoint(t_viewpoint *vp);
// void		julia_viewpoint(t_viewpoint *v);
// void		burningship_viewpoint(t_viewpoint *v);
// double		atod_check(char *str, int *error);
// void		render(t_mlx *mlx);
// int			terminate_fractol(t_mlx *mlx);
// void		reset_viewpoint(t_mlx *mlx);
// int			error_return_zero(int *error);

// #endif