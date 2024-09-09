/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:19:15 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:21:21 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	generate_random_noise(int t)
{
	t = (t << 13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return (1.0 - (t & 0x7fffffff) / 1073741824.0);
}

double	generate_2d_noise(int x, int y)
{
	int	temp;

	temp = generate_random_noise(x) * 850000;
	return (generate_random_noise(temp + y));
}

double	generate_smooth_noise(int x, int y)
{
	double	corners;
	double	sides;
	double	center;

	corners = (generate_2d_noise(x - 1, y - 1) + generate_2d_noise(x + 1, y - 1)
			+ generate_2d_noise(x - 1, y + 1)
			+ generate_2d_noise(x + 1, y + 1)) / 16.0;
	sides = (generate_2d_noise(x - 1, y) + generate_2d_noise(x + 1, y)
			+ generate_2d_noise(x, y - 1) + generate_2d_noise(x, y + 1)) / 8.0;
	center = generate_2d_noise(x, y) / 4.0;
	return (corners + sides + center);
}
