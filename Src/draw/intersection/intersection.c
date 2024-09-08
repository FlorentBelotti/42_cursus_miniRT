/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:53:00 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/08 17:54:40 by fbelotti         ###   ########.fr       */
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

double	get_intersection_distance(t_object *object, t_ray *ray, int code)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
		d = sphere_intersection(&object->specific.sphere,
				ray, object, code);
	else if (object->type == CYLINDER)
	{
		d = cylinder_intersection(&object->specific.cylinder,
				ray, object, code);
		object->specific.cylinder.disk = 0;
	}
	else if (object->type == PLANE)
		d = plane_intersection(&object->specific.plane,
				ray, &object->pos);
	else if (object->type == CONE)
		d = cone_intersection(&object->specific.cone, ray,
				object, code);
	return (d);
}
