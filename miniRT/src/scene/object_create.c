#include "scene.h"

t_object    *object(t_object_type type, void *element, t_color3 albedo)
{
    t_object    *new;

    if (!(new = (t_object *)malloc(sizeof(t_object))))
        return (NULL);
    new->type = type;
    new->element = element;
    new->next = NULL;
    new->albedo = albedo;
    return (new);
}

t_sphere    *sphere(t_point3 center, double radius)
{
    t_sphere *sp;

    if(!(sp = (t_sphere *)malloc(sizeof(t_sphere))))
        return (NULL);
    sp->center = center;
    sp->radius = radius;
    sp->radius2 = radius * radius;
    return (sp);
}

	// t_point3	center; // 평면위의 한점
	// t_vec3		dir;	// 방향

t_plane    *splane(t_point3 center, t_vec3 dir)
{
    t_plane *pl;

    if(!(pl = (t_plane *)malloc(sizeof(t_plane))))
        return (NULL);
    pl->center = center;
    pl->dir = dir;
    return (pl);
}

// struct s_cylinder
// {
// 	t_point3	center; // 평면위의 한점
// 	t_vec3		dir;	// 방향
// 	double		diameter; //
// 	double		height;
// };

t_cylinder	*scylinder(t_point3 center, t_vec3 dir, double diameter, double height)
{
    t_cylinder *cy;
    if (!(cy = (t_cylinder *)malloc(sizeof(t_cylinder))))
        return (NULL);
    cy->center = center;
    cy->dir = dir;
    cy->diameter = diameter;
    cy->height = height;
    return (cy);
}

t_light     *light_point(t_point3 light_origin, t_color3 light_color, double bright_ratio)
{
    t_light *light;

    if(!(light = (t_light *)malloc(sizeof(t_light))))
        return (NULL);
    light->origin = light_origin;
    light->light_color = light_color;
    light->bright_ratio = bright_ratio;
    return (light);
}