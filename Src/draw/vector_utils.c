/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:34 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/06 19:33:21 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_vector	get_oc_vector(t_vector *ray_origin, t_vector *object_center)
{
	t_vector vector_oc;

	vector_oc.x = ray_origin->x - object_center->x;
	vector_oc.y = ray_origin->y - object_center->y;
	vector_oc.z = ray_origin->z - object_center->z;
	return (vector_oc);
}

void	normalize_vector(t_vector *v)
{
	double norm;

	norm = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	if (norm != 0)
	{
		v->x /= norm;
		v->y /= norm;
		v->z /= norm;
	}
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

t_vector add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return (result);
}

t_vector sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return (result);
}

t_vector mul(t_vector a, double b)
{
	t_vector	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;

	return (result);
}

double	get_scalar_product(const t_vector *a, const t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	square(double x)
{
	return (x * x);
}

double	get_delta(t_inter *inter)
{
	return (square(inter->coef_b) - (4 * inter->coef_a * inter->coef_c));
}
