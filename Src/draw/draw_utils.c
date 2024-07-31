/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:34 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/01 00:20:04 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_vector	*get_oc_vector(t_vector *ray_origin, t_vector *object_center)
{
	t_vector *vector_oc;

	vector_oc = (t_vector *)malloc(sizeof(t_vector));
	if (!vector_oc)
		return (NULL);
	vector_oc->x = ray_origin->x - object_center->x;
	vector_oc->y = ray_origin->y - object_center->y;
	vector_oc->z = ray_origin->z - object_center->z;
	return (vector_oc);
}

t_vector	vector_cross(t_vector a, t_vector b)
{
	t_vector cross;

	cross.x = a.y * b.z - a.z * b.y;
	cross.y = a.z * b.x - a.x * b.z;
	cross.z = a.x * b.y - a.y * b.x;
	return (cross);
}

t_vector	vector_subtract(t_vector a, t_vector b)
{
	t_vector sub;

	sub.x = a.x - b.x;
	sub.y = a.y - b.y;
	sub.z = a.z - b.z;
	return (sub);
}
