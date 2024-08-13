/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:52:10 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/13 14:12:05 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	get_ambient_light(t_ambient ambient, t_color object_color)
{
	t_color	result;

	result.r = (int)(object_color.r * ambient.ratio * (ambient.color.r / 255.0));
	result.g = (int)(object_color.g * ambient.ratio * (ambient.color.g / 255.0));
	result.b = (int)(object_color.b * ambient.ratio * (ambient.color.b / 255.0));
	result.r = fmin(result.r, 255);
	result.g = fmin(result.g, 255);
	result.b = fmin(result.b, 255);
	return (result);
}

static t_color	get_plane_lightning(t_light light, t_object *object, t_vector intersection)
{
	t_vector	light_dir;
	t_color		diffuse_color;
	double		intensity;

	light_dir = sub(light.pos, intersection);
	normalize_vector(&light_dir);
	intensity = fmax(0.0, get_scalar_product(&object->specific.plane.normal, &light_dir)) * light.brightness;
	diffuse_color.r = fmin((int)(object->color.r * intensity * (light.color.r / 255.0)), 255);
	diffuse_color.g = fmin((int)(object->color.g * intensity * (light.color.g / 255.0)), 255);
	diffuse_color.b = fmin((int)(object->color.b * intensity * (light.color.b / 255.0)), 255);
	return (diffuse_color);
}

static t_color get_sphere_lightning(t_light light, t_object *object, t_vector intersection)
{
	t_vector normal;
	t_vector light_dir;
	t_color diffuse_color;
	double intensity;

	light_dir = sub(light.pos, intersection);
	normalize_vector(&light_dir);
	normal = sub(intersection, object->pos);
	normalize_vector(&normal);
	intensity = fmax(0.0, get_scalar_product(&normal, &light_dir)) * light.brightness;
	diffuse_color.r = fmin((int)(object->color.r * intensity * (light.color.r / 255.0)), 255);
	diffuse_color.g = fmin((int)(object->color.g * intensity * (light.color.g / 255.0)), 255);
	diffuse_color.b = fmin((int)(object->color.b * intensity * (light.color.b / 255.0)), 255);
	return (diffuse_color);
}

static t_color get_cylinder_lightning(t_light light, t_object *object, t_vector intersection)
{
	t_vector normal;
	t_vector light_dir;
	t_vector projection;
	t_vector oc;
	t_color diffuse_color;
	double intensity;

	light_dir = sub(light.pos, intersection);
	normalize_vector(&light_dir);
	oc = sub(intersection, object->pos);
	projection = mul(object->specific.cylinder.axis, get_scalar_product(&oc, &object->specific.cylinder.axis));
	normal = sub(oc, projection);
	normalize_vector(&normal);
	intensity = fmax(0.0, get_scalar_product(&normal, &light_dir)) * light.brightness;
	diffuse_color.r = fmin((int)(object->color.r * intensity * (light.color.r / 255.0)), 255);
	diffuse_color.g = fmin((int)(object->color.g * intensity * (light.color.g / 255.0)), 255);
	diffuse_color.b = fmin((int)(object->color.b * intensity * (light.color.b / 255.0)), 255);
	return (diffuse_color);
}


static t_color get_diffuse_light(t_light light, t_object *object, t_vector intersection)
{
	t_color	diffuse_color;

	diffuse_color.r = 0;
	diffuse_color.g = 0;
	diffuse_color.b = 0;
	if (object->type == PLANE)
		diffuse_color = get_plane_lightning(light, object, intersection);
	else if (object->type == SPHERE)
		diffuse_color = get_sphere_lightning(light, object, intersection);
	else if (object->type == CYLINDER)
		diffuse_color = get_cylinder_lightning(light, object, intersection);
	return (diffuse_color);
}

static double	get_light_distance(t_vector a, t_vector b)
{
	t_vector	diff;
	double		result;

	diff = vector_subtract(a, b);
	result = sqrt(get_scalar_product(&diff, &diff));
	return (result);
}

int		is_in_shadow(t_data *data, t_vector intersection, t_light light)
{
	t_ray		shadow_ray;
	t_object	*current_object;
	double		d;
	double		d_light;

	shadow_ray.direction = sub(light.pos, intersection);
	normalize_vector(&shadow_ray.direction);
	shadow_ray.origin = add(intersection, mul(shadow_ray.direction, EPSILON));
	d_light = get_light_distance(light.pos, shadow_ray.origin);
	current_object = data->objects;
	while (current_object)
	{
		d = check_for_intersections(current_object, &shadow_ray);
		if (d > EPSILON && d < d_light)
			return (1);
		current_object = current_object->next;
	}
	return (0);
}

t_color	get_pixel_lightning(t_data *data, t_object *object, t_vector intersection)
{
	t_color	ambient_color;
	t_color	diffuse_color;
	t_color	final_color;

	ambient_color = get_ambient_light(data->ambient, object->color);
	if (is_in_shadow(data, intersection, data->light) == 0)
	{
		diffuse_color = get_diffuse_light(data->light, object, intersection);
		final_color.r = fmin(ambient_color.r + diffuse_color.r, 255);
		final_color.g = fmin(ambient_color.g + diffuse_color.g, 255);
		final_color.b = fmin(ambient_color.b + diffuse_color.b, 255);
	}
	else
	{
		final_color.r = fmin(ambient_color.r, 255);
		final_color.g = fmin(ambient_color.g, 255);
		final_color.b = fmin(ambient_color.b, 255);
	}
	return (final_color);
}
