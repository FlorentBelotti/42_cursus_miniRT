/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:47:12 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/08 17:35:30 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../Includes/miniRT.h"

// t_vector rotate_vector(t_vector v, t_vector axis, double theta)
// {
// 	t_vector rotated_vec;
// 	double cos_theta = cos(theta);
// 	double sin_theta = sin(theta);
// 	t_vector cross = vector_cross(axis, v);
// 	double dot = get_scalar_product(&axis, &v);
// 	rotated_vec.x = v.x * cos_theta + cross.x * sin_theta + axis.x * dot * (1 - cos_theta);
// 	rotated_vec.y = v.y * cos_theta + cross.y * sin_theta + axis.y * dot * (1 - cos_theta);
// 	rotated_vec.z = v.z * cos_theta + cross.z * sin_theta + axis.z * dot * (1 - cos_theta);
// 	return rotated_vec;
// }

// double paraboloid_intersection(t_paraboloid *parab, t_ray *ray, t_object *current, int code)
// {
// 	t_inter inter;
// 	double a, b;
// 	t_vector rotated_origin, rotated_direction;
// 	double theta;

// 	theta = acos(parab->orient.z);
// 	rotated_origin = rotate_vector(ray->origin, parab->orient, theta);
// 	rotated_direction = rotate_vector(ray->direction, parab->orient, theta);
// 	inter.oc = get_oc_vector(&rotated_origin, &current->pos);
// 	a = parab->demi_axe_a;
// 	b = parab->demi_axe_b;
// 	inter.coef_a = (rotated_direction.x * rotated_direction.x) / (a * a) +
// 			(rotated_direction.y * rotated_direction.y) / (b * b);
// 	inter.coef_b = 2 * ((inter.oc.x * rotated_direction.x) / (a * a) +
// 			(inter.oc.y * rotated_direction.y) / (b * b)) - 2 * rotated_direction.z;
// 	inter.coef_c = (inter.oc.x * inter.oc.x) / (a * a) +
// 			(inter.oc.y * inter.oc.y) / (b * b) - 2 * inter.oc.z;
// 	inter.delta = get_delta(&inter);
// 	if (inter.delta < 0)
// 		return (-1);
// 	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
// 	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
// 	return (return_high_or_low(inter, code));
// }


