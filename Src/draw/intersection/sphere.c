/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:51:04 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/26 15:23:11 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	sphere_intersection(t_sphere *sphere, t_ray *ray, t_object *current, int code)
{
	t_inter	inter;

	inter.oc = get_oc_vector(&ray->origin, &current->pos);
	inter.radius = sphere->diameter / 2;
	inter.coef_a = get_scalar_product(&ray->direction, &ray->direction);
	inter.coef_b = 2 * get_scalar_product(&inter.oc, &ray->direction);
	inter.coef_c = get_scalar_product(&inter.oc, &inter.oc)
		- square(inter.radius);
	inter.delta = get_delta(&inter);
	if (inter.delta < 0)
		return (-1);
	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
	return (return_high_or_low(inter, code));
}
