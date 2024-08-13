/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:50:25 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/13 15:50:50 by fbelotti         ###   ########.fr       */
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
