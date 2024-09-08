/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:38:44 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/08 18:14:45 by fbelotti         ###   ########.fr       */
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
	geo_lim = 0;
	i = 0;
	while (i++ < octaves)
	{
		r += perlin(x * f, y * f) * amplitude;
		amplitude *= persistence;
		geo_lim += amplitude;
		f *= 2;
	}
	return (r / geo_lim);
}

static double	define_theta(t_object *object, t_vector *normal, t_vector intersection)
{
	t_vector	oc;
	t_vector	projection;
	t_vector	radial_vector;
	double		height;

	if (object->type == SPHERE)
		return (normal->x);
	else if (object->type == CYLINDER)
	{
		oc = sub(intersection, object->pos);
		height = get_scalar_product(&oc, &object->specific.cylinder.axis);
		projection = mul(object->specific.cylinder.axis, height);
		radial_vector = sub(oc, projection);
		return (atan2(radial_vector.y, radial_vector.x));
	}
	else if (object->type == PLANE)
		return (intersection.x);
	return (normal->x);
}

static double	define_height(t_object *object, t_vector *normal, t_vector intersection)
{
	t_vector	oc;

	if (object->type == SPHERE)
		return (normal->y);
	else if (object->type == CYLINDER)
	{
		if (object->specific.cylinder.disk > 0)
			return (intersection.z);
		oc = sub(intersection, object->pos);
		return (get_scalar_product(&oc, &object->specific.cylinder.axis));
	}
	else if (object->type == CONE)
	{
		oc = sub(intersection, object->pos);
		return (get_scalar_product(&oc, &object->specific.cone.axis));
	}
	else if (object->type == PLANE)
		return (intersection.z);
	return (normal->y);
}

void perturb_normal(t_vector *normal, t_object *object, t_vector intersection)
{
	double	theta;
	double	height;
	double	noise_value;

	theta = define_theta(object, normal, intersection);
	height = define_height(object, normal, intersection);
	noise_value = get_noise_value(object->noise.octaves,
			object->noise.frequency, object->noise.persistence, theta, height);
	normal->x += noise_value * object->noise.intensity;
	normal->y += noise_value * object->noise.intensity;
	normal->z += noise_value * object->noise.intensity;
	//normalize_vector(normal);
}
