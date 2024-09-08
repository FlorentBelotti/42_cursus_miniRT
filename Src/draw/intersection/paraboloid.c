/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:47:12 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/08 00:10:10 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../Includes/miniRT.h"

// t_vector	rotate_vector(t_vector v, t_vector axis)
// {
// 	t_vector	rotated_vec;
// 	double		cos_theta;
// 	double		sin_theta;
// 	t_vector	cross_product;
// 	double		dot_product;

// 	axis = normalize_vector(axis);
// 	cos_theta = axis.z; // Composante z de l'axe
// 	sin_theta = sqrt(1 - cos_theta * cos_theta); // sin(θ) = sqrt(1 - cos^2(θ))
// 	cross_product = cross_product_vector(axis, v);
// 	dot_product = dot_product_vector(axis, v);
// 	rotated_vec.x = v.x * cos_theta + cross_product.x * sin_theta + axis.x * dot_product * (1 - cos_theta);
// 	rotated_vec.y = v.y * cos_theta + cross_product.y * sin_theta + axis.y * dot_product * (1 - cos_theta);
// 	rotated_vec.z = v.z * cos_theta + cross_product.z * sin_theta + axis.z * dot_product * (1 - cos_theta);
// 	return (rotated_vec);
// }


// double	paraboloid_intersection(t_paraboloid *parab, t_ray *ray, t_object *current, int code)
// {
// 	t_inter		inter;
// 	double		a;
// 	double		b;
// 	t_vector	rotated_origin;
// 	t_vector	rotated_direction;

// 	rotated_origin = rotate_vector(ray->origin, parab->orient);
// 	rotated_direction = rotate_vector(ray->direction, parab->orient);
// 	inter.oc = get_oc_vector(&rotated_origin, &current->pos);
// 	a = parab->a;
// 	b = parab->b;
// 	inter.coef_a = (rotated_direction.x * rotated_direction.x) / (a * a) + (rotated_direction.y * rotated_direction.y) / (b * b);
// 	inter.coef_b = 2 * ((inter.oc.x * rotated_direction.x) / (a * a) + (inter.oc.y * rotated_direction.y) / (b * b)) - 2 * rotated_direction.z;
// 	inter.coef_c = (inter.oc.x * inter.oc.x) / (a * a) + (inter.oc.y * inter.oc.y) / (b * b) - 2 * inter.oc.z;
// 	inter.delta = get_delta(&inter);
// 	if (inter.delta < 0)
// 		return (-1);
// 	inter.r1 = (-inter.coef_b - sqrt(inter.delta)) / (2 * inter.coef_a);
// 	inter.r2 = (-inter.coef_b + sqrt(inter.delta)) / (2 * inter.coef_a);
// 	return (return_high_or_low(inter, code));
// }
