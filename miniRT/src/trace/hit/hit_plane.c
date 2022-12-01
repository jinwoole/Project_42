/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sooyokim <sooyokim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:43:32 by sooyokim          #+#    #+#             */
/*   Updated: 2022/11/08 10:49:04 by sooyokim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "utils.h"
#include "trace.h"
// static int test1 = 0;

t_bool      hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
{
    t_plane *pl = pl_obj->element;
    // float numrator; // 판별식의 분자
    // float denominator; // 판별식의 분모
    // float root;
	double numrator; // 판별식의 분자
    double denominator; // 판별식의 분모
    double root;
    denominator = vdot(ray->dir, pl->dir);
    if (fabs(denominator) < EPSILON) // 분모의 값이 0보다 작거나 같을 경우 충돌하지 않는다.
        return (FALSE);
    numrator = vdot(vminus(pl->center, ray->orig), pl->dir);
    root = numrator / denominator;
    if (root < rec->tmin || rec->tmax < root) 
        return (FALSE);
	// printf("pass test\n");
    rec->t = root;
    rec->p = ray_at(ray, root);    
    rec->normal = pl->dir;
	// set_face_normal(ray, rec);
	rec->albedo = pl_obj->albedo;	
    // print_vec(normal);
	// printf("test %d : \n", test1++);
    return (TRUE);
}

// t_bool	hit_plane(t_object *pl_obj, t_ray *ray, t_hit_record *rec)
// {
// 	t_plane	*pl;
// 	float	numrator;
// 	float	denominator;
// 	float	root;

// 	pl = pl_obj->element;
// 	denominator = vdot(ray->dir, pl->dir);
// 	if (fabs(denominator) < EPSILON)
// 		return (FALSE);
// 	numrator = vdot(vminus(pl->center, ray->orig), pl->dir);
// 	root = numrator / denominator;
// 	if (root < rec->tmin || rec->tmax < root)
// 		return (FALSE);
// 	rec->t = root;
// 	rec->p = ray_at(ray, root);
// 	rec->normal = pl->dir;
// 	set_face_normal(ray, rec);
// 	rec->albedo = pl_obj->albedo; // 이부분 확실하지 않음 컬러인지 알베도인지 체크
// 	return (TRUE);
// }