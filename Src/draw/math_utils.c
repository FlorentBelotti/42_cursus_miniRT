/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:57:04 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/06 17:00:54 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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
