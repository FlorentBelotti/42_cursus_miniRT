/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:53:00 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/26 01:31:19 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_vector	get_oc_vector(t_vector *ray_origin, t_vector *object_center)
{
	t_vector	vector_oc;

	vector_oc.x = ray_origin->x - object_center->x;
	vector_oc.y = ray_origin->y - object_center->y;
	vector_oc.z = ray_origin->z - object_center->z;
	return (vector_oc);
}

void	normalize_vector(t_vector *v)
{
	double	norm;

	norm = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	v->x /= norm;
	v->y /= norm;
	v->z /= norm;
}

static double sphere_intersection_max(t_sphere *sphere, t_ray *ray, t_object *current)
{
	t_inter inter;

	inter.oc = get_oc_vector(&ray->origin, &current->pos);
	inter.radius = sphere->diameter / 2;
	inter.coef_a = get_scalar_product(&ray->direction, &ray->direction);
	inter.coef_b = 2 * get_scalar_product(&inter.oc, &ray->direction);
	inter.coef_c = get_scalar_product(&inter.oc, &inter.oc) - square(inter.radius);
	inter.delta = get_delta(&inter);
	if (inter.delta < 0)
		return (-1);
	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
	if (inter.r1 > EPSILON && inter.r2 > EPSILON)
		return fmax(inter.r1, inter.r2);
	else if (inter.r1 > EPSILON)
		return inter.r1;
	else if (inter.r2 > EPSILON)
		return inter.r2;
	return (-1);
}

double	get_low_intersection_distance(t_object *object, t_ray *ray)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
		d = sphere_intersection(&object->specific.sphere,
				ray, object);
	else if (object->type == CYLINDER)
		d = cylinder_intersection(&object->specific.cylinder,
				ray, object);
	else if (object->type == PLANE)
		d = plane_intersection(&object->specific.plane,
				ray, &object->pos);
	return (d);
}

double	get_high_intersection_distance(t_object *object, t_ray *ray)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
		d = sphere_intersection_max(&object->specific.sphere,
				ray, object);
	else if (object->type == CYLINDER)
		d = cylinder_intersection(&object->specific.cylinder,
				ray, object);
	else if (object->type == PLANE)
		d = plane_intersection(&object->specific.plane,
				ray, &object->pos);
	return (d);
}
