/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:08:31 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/22 16:29:32 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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
