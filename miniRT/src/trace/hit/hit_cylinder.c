/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:26:15 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/08 10:21:26 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

int	hit_cy_cap(t_object *cy_obj, t_ray *ray, t_hit_record *rec, double height)
{
	t_cylinder	*cy;
	double		r;
	t_vec3		center;
	float		root; // float쓸지 double 쓸지 파악 필요
	float		diameter;

	cy = cy_obj->element;
	r = cy->diameter / 2;
	center = vplus(cy->center, vmult(cy->dir, height));
	root = vdot(vminus(center, ray->orig), cy->dir) / vdot(ray->dir, cy->dir);
	diameter = vlength(vminus(center, ray_at(ray, root)));
	if (fabs(r) < fabs(diameter))
		return (0);
	if (root < rec->tmin || rec->tmax < root)
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->tmax = rec->t;
	if (height > 0)
		rec->normal = cy->dir;
	else
		rec->normal = vmult(cy->dir, -1);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}

t_bool	hit_cylinder(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	const t_cylinder	*cy = cy_obj->element;
	int					result;

	result = 0;

	result += hit_cy_cap(cy_obj, ray, rec, -(cy->height / 2));
	result += hit_cy_cap(cy_obj, ray, rec, cy->height / 2);
	result += hit_cylinder_side(cy_obj, ray, rec);
	return (result);
}
