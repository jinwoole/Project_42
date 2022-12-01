/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:30:35 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/08 10:19:46 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"

int	cy_boundary(t_cylinder *cy, t_vec3 at_point)
{
	double	hit_height;
	double	max_height;

	hit_height = vdot(vminus(at_point, cy->center), cy->dir);
	max_height = cy->height / 2;
	if (fabs(hit_height) > max_height)
		return (0);
	return (1);
}

t_vec3	get_cylinder_normal(t_cylinder *cy, t_vec3 at_point, double hit_height)
{
	t_point3	hit_center;
	t_vec3		normal;

	hit_center = vplus(cy->center, vmult(cy->dir, hit_height));
	normal = vminus(at_point, hit_center);
	return (vunit(normal));
}

double	cy_discriminant(t_object *cy_obj, t_ray *ray, double *half_b, double *a)
{
	t_cylinder	*cy;
	double		c;
	double		r;
	double		discriminant;
	t_vec3		delta_p;

	cy = cy_obj->element;
	r = cy->diameter / 2;
	delta_p = vminus(ray->orig, cy->center);
	(*a) = vlength2(vcross(ray->dir, cy->dir));
	(*half_b) = vdot(vcross(ray->dir, cy->dir), vcross(delta_p, cy->dir));
	c = vlength2(vcross(delta_p, cy->dir)) - pow(r, 2);
	discriminant = (*half_b) * (*half_b) - (*a) * c;
	return (discriminant);
}

int	hit_cylinder_side(t_object *cy_obj, t_ray *ray, t_hit_record *rec)
{
	double	a;
	double	half_b;
	double	discriminant;
	double	root;
	double	hit_height;

	discriminant = cy_discriminant(cy_obj, ray, &half_b, &a);
	if (discriminant < 0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	hit_height = cy_boundary(cy_obj->element, ray_at(ray, root));
	if (!(hit_height))
		return (0);
	rec->t = root;
	rec->p = ray_at(ray, root);
	rec->normal = get_cylinder_normal(cy_obj->element, rec->p, hit_height);
	set_face_normal(ray, rec);
	rec->albedo = cy_obj->albedo;
	return (1);
}
