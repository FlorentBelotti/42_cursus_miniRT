/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:51:04 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/12 23:16:43 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double sphere_intersection(t_sphere *sphere, t_ray *ray, t_object *current)
{
	t_inter inter;

	inter.oc = get_oc_vector(&ray->origin, &current->pos);
	inter.radius = sphere->diameter / 2;
	inter.coef_a = get_scalar_product(&ray->direction, &ray->direction);
	inter.coef_b = 2 * get_scalar_product(&inter.oc, &ray->direction);
	inter.coef_c = get_scalar_product(&inter.oc, &inter.oc) - square(inter.radius);
	inter.delta = get_delta(&inter);
	if (inter.delta < 0)
		return (-1);
	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
	if (inter.r1 > EPSILON && (inter.r1 < inter.r2 || inter.r2 <= EPSILON))
		return (inter.r1);
	if (inter.r2 > EPSILON)
		return (inter.r2);
	return (-1);
}

static t_vector get_cylinder_center(t_vector base_center, t_vector axis, double height)
{
	t_vector center;

	center.x = base_center.x + axis.x * height / 2;
	center.y = base_center.y + axis.y * height / 2;
	center.z = base_center.z + axis.z * height / 2;
	return (center);
}

double cylinder_intersection(t_cylinder *cylinder, t_ray *ray, t_object *current)
{
	t_inter		inter;
	t_vector	oc_perp;
	t_vector	dir_perp;
	t_vector	P1;
	t_vector	P2;
	t_vector	cylinder_center;
	double		oc_v;
	double		ray_dir_v;
	double		P1_proj;
	double		P2_proj;
	double		cylinder_min;
	double		cylinder_max;
	double		closest_intersection;

	closest_intersection = -1;
	inter.radius = cylinder->diameter / 2;
	inter.oc = get_oc_vector(&ray->origin, &current->pos);

	// Calcul des projections sur l'axe du cylindre

	oc_v = get_scalar_product(&inter.oc, &cylinder->axis);
	ray_dir_v = get_scalar_product(&ray->direction, &cylinder->axis);

	// Calcul des composantes perpendiculaires aux projections

	oc_perp.x = inter.oc.x - oc_v * cylinder->axis.x;
	oc_perp.y = inter.oc.y - oc_v * cylinder->axis.y;
	oc_perp.z = inter.oc.z - oc_v * cylinder->axis.z;
	dir_perp.x = ray->direction.x - ray_dir_v * cylinder->axis.x;
	dir_perp.y = ray->direction.y - ray_dir_v * cylinder->axis.y;
	dir_perp.z = ray->direction.z - ray_dir_v * cylinder->axis.z;

	// Calcul des coefficients de l'équation quadratique

	inter.coef_a = get_scalar_product(&dir_perp, &dir_perp);
	inter.coef_b = 2 * get_scalar_product(&oc_perp, &dir_perp);
	inter.coef_c = get_scalar_product(&oc_perp, &oc_perp) - square(inter.radius);
	inter.delta = get_delta(&inter);
	if (inter.delta < 0)
		return (-1);

	// Calcul des distances des points d'intersection

	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);

	// Calcul des points d'intersection sur le cylindre

	cylinder_center = get_cylinder_center(current->pos, cylinder->axis, cylinder->height);
	P1.x = ray->origin.x + inter.r1 * ray->direction.x;
	P1.y = ray->origin.y + inter.r1 * ray->direction.y;
	P1.z = ray->origin.z + inter.r1 * ray->direction.z;
	P2.x = ray->origin.x + inter.r2 * ray->direction.x;
	P2.y = ray->origin.y + inter.r2 * ray->direction.y;
	P2.z = ray->origin.z + inter.r2 * ray->direction.z;

	// Projections des points d'intersection sur l'axe du cylindre

	P1_proj = get_scalar_product(&P1, &cylinder->axis);
	P2_proj = get_scalar_product(&P2, &cylinder->axis);

	// Détermination des limites du cylindre

	cylinder_min = get_scalar_product(&cylinder_center, &cylinder->axis) - (cylinder->height / 2);
	cylinder_max = get_scalar_product(&cylinder_center, &cylinder->axis) + (cylinder->height / 2);

	// Vérification si les points d'intersection sont dans les limites du cylindre

	if (P1_proj >= cylinder_min && P1_proj <= cylinder_max && inter.r1 > 0)
		closest_intersection = inter.r1;
	if (P2_proj >= cylinder_min && P2_proj <= cylinder_max && inter.r2 > 0)
	{
		if (closest_intersection == -1 || inter.r2 < closest_intersection)
			closest_intersection = inter.r2;
	}
	if (closest_intersection > 0)
		return (closest_intersection);
	return (-1);
}

double plane_intersection(t_plane *plane, t_ray *ray, t_object *current)
{
	t_vector plane_origin;
	double t;
	double denominator;

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
