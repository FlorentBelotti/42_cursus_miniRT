/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:52:53 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 15:49:35 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_vector	get_closest_cap_normal(t_cylinder *cylinder, t_object *object,
		t_vector intersection)
{
	t_vector	base_center;
	t_vector	top_center;
	double		distance_to_base;
	double		distance_to_top;

	base_center = object->pos;
	top_center = add(base_center, mul(cylinder->axis, cylinder->height));
	distance_to_base = get_light_distance(intersection, base_center);
	distance_to_top = get_light_distance(intersection, top_center);
	if (distance_to_top < distance_to_base)
		return (cylinder->axis);
	else
		return (mul(cylinder->axis, -1));
}

static double	get_disk_intersection(t_object *object, t_inter *inter,
		t_ray *ray, double t)
{
	double		distance_to_center;
	t_vector	intersection;
	t_vector	diff;

	intersection = add(ray->origin, mul(ray->direction, t));
	diff = sub(intersection, inter->cap_pos);
	distance_to_center = sqrt(get_scalar_product(&diff, &diff));
	if (distance_to_center <= inter->radius + EPSILON)
	{
		object->specific.cylinder.disk += 1;
		return (t);
	}
	return (inter->closest);
}

double	plane_disk_intersection(t_object *object, t_inter *inter,
		t_ray *ray, int code)
{
	t_plane		plane;
	double		t;

	plane.normal = get_closest_cap_normal(&object->specific.cylinder,
			object, inter->cap_pos);
	t = plane_intersection(&plane, ray, &inter->cap_pos);
	if (code == -1)
	{
		if (t > EPSILON && (inter->closest == -1
				|| t <= inter->closest - EPSILON))
			return (get_disk_intersection(object, inter, ray, t));
	}
	else if (code == 1)
	{
		if (t > EPSILON && (inter->closest == -1
				|| t >= inter->closest - EPSILON))
			return (get_disk_intersection(object, inter, ray, t));
	}
	return (inter->closest);
}
