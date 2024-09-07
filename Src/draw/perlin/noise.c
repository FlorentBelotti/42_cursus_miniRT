/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:38:44 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/06 15:48:06 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	generate_random_noise(int t)
{
	t = (t<<13) ^ t;
	t = (t * (t * t * 15731 + 789221) + 1376312589);
	return 1.0 - (t & 0x7fffffff) / 1073741824.0;
}

double	generate_2d_noise(int x, int y)
{
	int temp;

	temp = generate_random_noise(x) * 850000;
	return (generate_random_noise(temp + y));
}

double linear_interpolation(double a, double b, double t)
{
	return ((1. - t) * a + t * b);
}

double generate_smooth_noise(int x, int y)
{
	double corners = (generate_2d_noise(x-1, y-1) + generate_2d_noise(x+1, y-1) + generate_2d_noise(x-1, y+1) + generate_2d_noise(x+1, y+1)) / 16.0;
	double sides = (generate_2d_noise(x-1, y) + generate_2d_noise(x+1, y) + generate_2d_noise(x, y-1) + generate_2d_noise(x, y+1)) / 8.0;
	double center = generate_2d_noise(x, y) / 4.0;
	return corners + sides + center;
}

double perlin(double x, double y)
{
	int int_x = (int)floor(x);
	int int_y = (int)floor(y);
	double frac_x = x - int_x;
	double frac_y = y - int_y;
	double a = generate_smooth_noise(int_x, int_y);
	double b = generate_smooth_noise(int_x + 1, int_y);
	double c = generate_smooth_noise(int_x, int_y + 1);
	double d = generate_smooth_noise(int_x + 1, int_y + 1);
	double interpolate_x1 = linear_interpolation(a, b, frac_x);
	double interpolate_x2 = linear_interpolation(c, d, frac_x);
	return (linear_interpolation(interpolate_x1, interpolate_x2, frac_y));
}

double perlin_2d(int octaves, double frequency, double persistence, double x, double y)
{
	double r = 0.0;
	double f = frequency;
	double amplitude = 1.0;
	for (int i = 0; i < octaves; i++)
	{
		r += perlin(x * f, y * f) * amplitude;
		amplitude *= persistence;
		f *= 2;
	}
	double geo_lim = (1 - persistence) / (1 - amplitude);
	return r * geo_lim;
}

void perturb_normal(t_vector *normal)
{
	// Paramètres pour le bruit de Perlin
	int octaves = 4;
	double frequency = 10;
	double persistence = 10;
	double intensity = 10; // Facteur de perturbation
	// Coordonnées de l'intersection ou tout autre paramètre requis
	double x = normal->x; // ou les coordonnées 2D/3D où appliquer le Perlin Noise
	double y = normal->y;
	// Calcul du bruit de Perlin
	double noise_value = perlin_2d(octaves, frequency, persistence, x, y);
	// Perturber la normale avec la valeur du bruit
	normal->x += noise_value * intensity;
	normal->y += noise_value * intensity;
	normal->z += noise_value * intensity;
	// Re-normalisation de la normale
	normalize_vector(normal);
}
