/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:38:44 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:22:22 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static double	get_noise_value(t_object *object, double x, double y)
{
	double	r;
	double	f;
	double	amplitude;
	double	geo_lim;
	int		i;

	r = 0.0;
	f = object->noise.frequency;
	amplitude = 1.0;
	geo_lim = 0;
	i = 0;
	while (i++ < object->noise.octaves)
	{
		r += perlin(x * f, y * f) * amplitude;
		amplitude *= object->noise.persistence;
		geo_lim += amplitude;
		f *= 2;
	}
	return (r / geo_lim);
}

static double	define_theta(t_object *object, t_vector *normal,
		t_vector intersection)
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

static double	define_height(t_object *object, t_vector *normal,
		t_vector intersection)
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

void	perturb_normal(t_vector *normal, t_object *object,
		t_vector intersection)
{
	double	theta;
	double	height;
	double	noise_value;

	theta = define_theta(object, normal, intersection);
	height = define_height(object, normal, intersection);
	noise_value = get_noise_value(object, theta, height);
	normal->x += noise_value * object->noise.intensity;
	normal->y += noise_value * object->noise.intensity;
	normal->z += noise_value * object->noise.intensity;
}
