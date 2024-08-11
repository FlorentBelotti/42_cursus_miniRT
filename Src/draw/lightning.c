/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:52:10 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/11 19:10:45 by fbelotti         ###   ########.fr       */
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

	normal = sub(intersection, object->pos);
	normalize_vector(&normal);
	light_dir = sub(light.pos, intersection);
	normalize_vector(&light_dir);
	intensity = fmax(0.0, get_scalar_product(&normal, &light_dir)) * light.brightness;
	diffuse_color.r = fmin((int)(object->color.r * intensity * (light.color.r / 255.0)), 255);
	diffuse_color.g = fmin((int)(object->color.g * intensity * (light.color.g / 255.0)), 255);
	diffuse_color.b = fmin((int)(object->color.b * intensity * (light.color.b / 255.0)), 255);
	return (diffuse_color);
}

static t_color get_diffuse_light(t_light light, t_object *object, t_vector intersection)
{
	t_color	diffuse_color;

	if (object->type == PLANE)
		diffuse_color = get_plane_lightning(light, object, intersection);
	else if (object->type == SPHERE)
		diffuse_color = get_sphere_lightning(light, object, intersection);
	/*else if (object->type == CYLINDER)
		diffuse_color = get_cylinder_lightning();*/
	return (diffuse_color);
}

t_color	get_pixel_lightning(t_data *data, t_object *object, t_vector intersection)
{
	t_color	ambient_color;
	t_color	diffuse_color;
	t_color	final_color;

	ambient_color = get_ambient_light(data->ambient, object->color);
	// add type check for object.
	diffuse_color = get_diffuse_light(data->light, object, intersection);
	final_color.r = fmin(ambient_color.r + diffuse_color.r, 255);
	final_color.g = fmin(ambient_color.g + diffuse_color.g, 255);
	final_color.b = fmin(ambient_color.b + diffuse_color.b, 255);
	return (final_color);
}
