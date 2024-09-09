/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 11:21:01 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:38 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static double	linear_interpolation(double a, double b, double t)
{
	return ((1. - t) * a + t * b);
}

double	perlin(double x, double y)
{
	t_perlin	parts;

	if (x >= 0)
		parts.int_x = (int)x;
	else
		parts.int_x = (int)x - 1;
	if (y >= 0)
		parts.int_y = (int)y;
	else
		parts.int_y = (int)y - 1;
	parts.frac_x = x - parts.int_x;
	parts.frac_y = y - parts.int_y;
	parts.a = generate_smooth_noise(parts.int_x, parts.int_y);
	parts.b = generate_smooth_noise(parts.int_x + 1, parts.int_y);
	parts.c = generate_smooth_noise(parts.int_x, parts.int_y + 1);
	parts.d = generate_smooth_noise(parts.int_x + 1, parts.int_y + 1);
	parts.interpolate_x1 = linear_interpolation(parts.a, parts.b,
			parts.frac_x);
	parts.interpolate_x2 = linear_interpolation(parts.c, parts.d,
			parts.frac_x);
	return (linear_interpolation(parts.interpolate_x1, parts.interpolate_x2,
			parts.frac_y));
}
