/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:38:44 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/07 11:33:29 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static double	generate_random_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return (1.0 - (t & 0x7fffffff) / 1073741824.0);
}

static double	generate_2d_noise(int x, int y)
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

	corners = (generate_2d_noise(x-1, y-1) + generate_2d_noise(x+1, y-1) + generate_2d_noise(x-1, y+1) + generate_2d_noise(x+1, y+1)) / 16.0;
	sides = (generate_2d_noise(x-1, y) + generate_2d_noise(x+1, y) + generate_2d_noise(x, y-1) + generate_2d_noise(x, y+1)) / 8.0;
	center = generate_2d_noise(x, y) / 4.0;
	return (corners + sides + center);
}

static double	get_noise_value(int octaves, double frequency, double persistence, double x, double y)
{
	double	r;
	double	f;
	double	amplitude;
	double	geo_lim;
	int		i;

	r = 0.0;
	f = frequency;
	amplitude = 1.0;
	i = 0;
	while (i++ < octaves)
	{
		r += perlin(x * f, y * f) * amplitude;
		amplitude *= persistence;
		f *= 2;
	}
	geo_lim = (1 - persistence) / (1 - amplitude);
	return (r * geo_lim);
}

void	perturb_normal(t_vector *normal)
{
	int		octaves;
	double	frequency;
	double	persistence;
	double	intensity;
	double	noise_value;

	octaves = 5;
	frequency = 5.0;
	persistence = 0.9;
	intensity = 0.4;
	noise_value = get_noise_value(octaves, frequency, persistence, normal->x, normal->y);
	normal->x += noise_value * intensity;
	normal->y += noise_value * intensity;
	normal->z += noise_value * intensity;
	//normalize_vector(normal);
}
