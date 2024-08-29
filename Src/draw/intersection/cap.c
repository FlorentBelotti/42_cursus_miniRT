/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:52:53 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/29 18:08:13 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_vector get_closest_cap_normal(t_vector light_pos, t_cylinder *cylinder, t_object *object)
{
	t_vector base_center;
	t_vector top_center;
	double distance_to_base;
	double distance_to_top;

	base_center = object->pos;
	top_center = add(object->pos, mul(cylinder->axis, cylinder->height));
	distance_to_base = get_light_distance(light_pos, base_center);
	distance_to_top = get_light_distance(light_pos, top_center);
	if (distance_to_base < distance_to_top)
		return (mul(cylinder->axis, -1));
	else
		return (cylinder->axis);
}

static double get_disk_intersection(t_object *object, t_inter *inter, t_ray *ray, double t)
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

double	plane_disk_intersection(t_object *object, t_inter *inter, t_ray *ray, int code)
{
	t_plane		plane;
	double		t;

	plane.normal = get_closest_cap_normal(ray->origin, &object->specific.cylinder, object);
	t = plane_intersection(&plane, ray, &inter->cap_pos);
	if (code == -1)
	{
		if (t > EPSILON && (inter->closest == -1 || t <= inter->closest - EPSILON))
			return (get_disk_intersection(object, inter, ray, t));
	}
	if (code == 1)
	{
		if (t > EPSILON && (inter->closest == -1 || t >= inter->closest - EPSILON))
			return (get_disk_intersection(object, inter, ray, t));
	}
	return (inter->closest);
}
