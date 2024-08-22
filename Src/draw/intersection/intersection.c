/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:53:00 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/22 16:30:31 by fbelotti         ###   ########.fr       */
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
	if (norm != 0)
	{
		v->x /= norm;
		v->y /= norm;
		v->z /= norm;
	}
}

int	check_for_intersections(t_object *object, t_ray *ray)
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
