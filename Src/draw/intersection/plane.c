/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:08:31 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/26 16:52:24 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	plane_disk_intersection(t_vector disk_center, t_cylinder *cylinder, double radius, t_ray *ray, double closest_intersection)
{
	t_plane		plane;
	t_vector	intersection_point;
	t_vector	diff;
	double		t;
	double		distance_to_center;

	plane.normal = mul(cylinder->axis, 0.5);
	t = plane_intersection(&plane, ray, &disk_center);
	if (t > EPSILON && (closest_intersection == -1 || t < closest_intersection - EPSILON))
	{
		cylinder->disk = 1;
		intersection_point = add(ray->origin, mul(ray->direction, t));
		diff = sub(intersection_point, disk_center);
		distance_to_center = sqrt(get_scalar_product(&diff, &diff));
		if (distance_to_center <= radius + EPSILON)
			return (t);
	}
	return (closest_intersection);
}

double	plane_intersection(t_plane *plane, t_ray *ray, t_vector *pos)
{
	t_vector	plane_origin;
	double		t;
	double		denominator;

	plane_origin.x = pos->x - ray->origin.x;
	plane_origin.y = pos->y - ray->origin.y;
	plane_origin.z = pos->z - ray->origin.z;
	denominator = get_scalar_product(&plane->normal, &ray->direction);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = get_scalar_product(&plane->normal, &plane_origin) / denominator;
	if (t > EPSILON)
		return (t);
	return (-1);
}
