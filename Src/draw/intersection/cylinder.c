/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:51:34 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/14 14:37:32 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static t_vector	get_cylinder_center(t_vector base_center, t_vector axis,
						double height)
{
	t_vector	center;

	center.x = base_center.x + axis.x * height / 2;
	center.y = base_center.y + axis.y * height / 2;
	center.z = base_center.z + axis.z * height / 2;
	return (center);
}

void	init_cylinder_intersection(t_inter *inter, t_cylinder *cylinder,
				t_ray *ray, t_object *current)
{
	inter->radius = cylinder->diameter / 2;
	inter->oc = get_oc_vector(&ray->origin, &current->pos);
	inter->oc_v = get_scalar_product(&inter->oc, &cylinder->axis);
	inter->ray_dir_v = get_scalar_product(&ray->direction, &cylinder->axis);
	inter->oc_perp.x = inter->oc.x - inter->oc_v * cylinder->axis.x;
	inter->oc_perp.y = inter->oc.y - inter->oc_v * cylinder->axis.y;
	inter->oc_perp.z = inter->oc.z - inter->oc_v * cylinder->axis.z;
	inter->dir_perp.x = ray->direction.x - inter->ray_dir_v * cylinder->axis.x;
	inter->dir_perp.x = ray->direction.x - inter->ray_dir_v * cylinder->axis.x;
	inter->dir_perp.y = ray->direction.y - inter->ray_dir_v * cylinder->axis.y;
	inter->dir_perp.z = ray->direction.z - inter->ray_dir_v * cylinder->axis.z;
}

int	calculate_quadratic_coef(t_inter *inter)
{
	inter->coef_a = get_scalar_product(&inter->dir_perp, &inter->dir_perp);
	inter->coef_b = 2 * get_scalar_product(&inter->oc_perp, &inter->dir_perp);
	inter->coef_c = get_scalar_product(&inter->oc_perp, &inter->oc_perp)
		- square(inter->radius);
	inter->delta = get_delta(inter);
	if (inter->delta < 0)
		return (0);
	return (1);
}

void	get_cylinder_intersection_points(t_inter *inter, t_cylinder *cylinder,
				t_ray *ray, t_object *current)
{
	inter->cylinder_center = get_cylinder_center(current->pos, cylinder->axis,
			cylinder->height);
	inter->P1.x = ray->origin.x + inter->r1 * ray->direction.x;
	inter->P1.y = ray->origin.y + inter->r1 * ray->direction.y;
	inter->P1.z = ray->origin.z + inter->r1 * ray->direction.z;
	inter->P2.x = ray->origin.x + inter->r2 * ray->direction.x;
	inter->P2.y = ray->origin.y + inter->r2 * ray->direction.y;
	inter->P2.z = ray->origin.z + inter->r2 * ray->direction.z;
	inter->P1_proj = get_scalar_product(&inter->P1, &cylinder->axis);
	inter->P2_proj = get_scalar_product(&inter->P2, &cylinder->axis);
	inter->cylinder_min = get_scalar_product(&inter->cylinder_center,
			&cylinder->axis) - (cylinder->height / 2);
	inter->cylinder_max = get_scalar_product(&inter->cylinder_center,
			&cylinder->axis) + (cylinder->height / 2);
}

double	cylinder_intersection(t_cylinder *cylinder, t_ray *ray,
			t_object *current)
{
	t_inter		inter;
	double		closest_intersection;

	closest_intersection = -1;
	init_cylinder_intersection(&inter, cylinder, ray, current);
	if (calculate_quadratic_coef(&inter) == 0)
		return (-1);
	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
	get_cylinder_intersection_points(&inter, cylinder, ray, current);
	if (inter.P1_proj >= inter.cylinder_min
		&& inter.P1_proj <= inter.cylinder_max && inter.r1 > 0)
		closest_intersection = inter.r1;
	if (inter.P2_proj >= inter.cylinder_min
		&& inter.P2_proj <= inter.cylinder_max && inter.r2 > 0)
	{
		if (closest_intersection == -1 || inter.r2 < closest_intersection)
			closest_intersection = inter.r2;
	}
	if (closest_intersection > 0)
		return (closest_intersection);
	return (-1);
}
