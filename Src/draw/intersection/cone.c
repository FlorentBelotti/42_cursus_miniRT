/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 17:35:37 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:01:02 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static void	init_cone_intersection(t_inter *inter, t_cone *cone,
		t_ray *ray, t_object *current)
{
	inter->radius = cone->diameter / 2;
	inter->oc = get_oc_vector(&ray->origin, &current->pos);
	inter->oc_v = get_scalar_product(&inter->oc, &cone->axis);
	inter->ray_dir_v = get_scalar_product(&ray->direction, &cone->axis);
	inter->oc_perp.x = inter->oc.x - inter->oc_v * cone->axis.x;
	inter->oc_perp.y = inter->oc.y - inter->oc_v * cone->axis.y;
	inter->oc_perp.z = inter->oc.z - inter->oc_v * cone->axis.z;
	inter->dir_perp.x = ray->direction.x - inter->ray_dir_v * cone->axis.x;
	inter->dir_perp.y = ray->direction.y - inter->ray_dir_v * cone->axis.y;
	inter->dir_perp.z = ray->direction.z - inter->ray_dir_v * cone->axis.z;
}

static int	calculate_cone_quadratic_coef(t_inter *inter, t_cone *cone)
{
	double	k;
	double	k2;

	k = (cone->diameter / 2.0) / cone->height;
	k2 = k * k;
	inter->coef_a = get_scalar_product(&inter->dir_perp, &inter->dir_perp)
		- k2 * (inter->ray_dir_v * inter->ray_dir_v);
	inter->coef_b = 2 * (get_scalar_product(&inter->oc_perp, &inter->dir_perp)
			- k2 * inter->oc_v * inter->ray_dir_v);
	inter->coef_c = get_scalar_product(&inter->oc_perp, &inter->oc_perp)
		- k2 * (inter->oc_v * inter->oc_v);
	inter->delta = get_delta(inter);
	if (inter->delta < 0)
		return (0);
	return (1);
}

static t_vector	get_cone_apex(t_vector base_center, t_vector axis,
		double height)
{
	t_vector	apex;

	apex.x = base_center.x + axis.x * height;
	apex.y = base_center.y + axis.y * height;
	apex.z = base_center.z + axis.z * height;
	return (apex);
}

static void	get_cone_intersection_points(t_inter *inter, t_cone *cone,
		t_ray *ray, t_object *current)
{
	inter->cone_apex = get_cone_apex(current->pos, cone->axis, cone->height);
	inter->P1.x = ray->origin.x + inter->r1 * ray->direction.x;
	inter->P1.y = ray->origin.y + inter->r1 * ray->direction.y;
	inter->P1.z = ray->origin.z + inter->r1 * ray->direction.z;
	inter->P2.x = ray->origin.x + inter->r2 * ray->direction.x;
	inter->P2.y = ray->origin.y + inter->r2 * ray->direction.y;
	inter->P2.z = ray->origin.z + inter->r2 * ray->direction.z;
	inter->P1_proj = get_scalar_product(&inter->P1, &cone->axis);
	inter->P2_proj = get_scalar_product(&inter->P2, &cone->axis);
	inter->c_min = get_scalar_product(&current->pos, &cone->axis);
	inter->c_max = get_scalar_product(&inter->cone_apex, &cone->axis);
}

double	cone_intersection(t_cone *cone, t_ray *ray, t_object *current, int code)
{
	t_inter	inter;

	inter.closest = -1;
	init_cone_intersection(&inter, cone, ray, current);
	if (calculate_cone_quadratic_coef(&inter, cone) == 0)
		return (-1);
	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
	get_cone_intersection_points(&inter, cone, ray, current);
	inter.closest = c_return_high_or_low(&inter, code);
	return (inter.closest);
}
