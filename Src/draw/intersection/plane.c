/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:08:31 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/13 14:11:14 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	plane_intersection(t_plane *plane, t_ray *ray, t_object *current)
{
	t_vector	plane_origin;
	double		t;
	double		denominator;

	plane_origin.x = current->pos.x - ray->origin.x;
	plane_origin.y = current->pos.y - ray->origin.y;
	plane_origin.z = current->pos.z - ray->origin.z;
	denominator = get_scalar_product(&plane->normal, &ray->direction);
	if (fabs(denominator) < EPSILON)
		return (0);
	t = get_scalar_product(&plane->normal, &plane_origin) / denominator;
	if (t > EPSILON)
		return (t);
	return (-1);
}
