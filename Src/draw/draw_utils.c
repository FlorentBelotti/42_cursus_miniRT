/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:34 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 00:13:44 by fbelotti         ###   ########.fr       */
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

double	get_scalar_product(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

double	get_delta(t_inter *inter)
{
	return (square(inter->coef_b) - 4 * inter->coef_a * inter->coef_c);
}

double	square(double x)
{
	return (x * x);
}
