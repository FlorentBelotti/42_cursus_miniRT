/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:52:10 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/26 01:17:50 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_color	get_diffuse_lighting(t_light light, t_vector normal, t_vector light_dir, t_color object_color, double shadow_factor, double d_light)
{
	t_color	diffuse;
	double	intensity;
	double	dot;

	dot = get_scalar_product(&normal, &light_dir);
	intensity = fmax(0.0, dot) * light.brightness;
	if (shadow_factor > 0 && shadow_factor < d_light)
		intensity *= 0.5;
	diffuse.r = fmin(object_color.r * intensity * (light.color.r / 255.0), 255.0);
	diffuse.g = fmin(object_color.g * intensity * (light.color.g / 255.0), 255.0);
	diffuse.b = fmin(object_color.b * intensity * (light.color.b / 255.0), 255.0);
	return (diffuse);
}

static t_vector	get_object_normal(t_vector intersection, t_object *object)
{
	t_vector	normal;
	t_vector	oc;
	t_vector	projection;

	if (object->type == SPHERE)
		normal = sub(intersection, object->pos);
	else if (object->type == PLANE)
		normal = object->specific.plane.normal;
	else if (object->type == CYLINDER)
	{
		oc = sub(intersection, object->pos);
		projection = mul(object->specific.cylinder.axis, get_scalar_product(&oc, &object->specific.cylinder.axis));
		normal = sub(oc, projection);
	}
	normalize_vector(&normal);
	return (normal);
}

t_color	get_pixel_lighting(t_data *data, t_object *object, t_vector intersection)
{
	t_vector	light_dir;
	t_vector	normal;
	t_color		ambient;
	t_color		color;
	t_color		diffuse;
	double		shadow_factor;
	double		d_light;

	ambient = get_ambient_light(data->ambient, object->color);
	light_dir = sub(data->light.pos, intersection);
	normalize_vector(&light_dir);
	normal = get_object_normal(intersection, object);
	d_light = get_light_distance(data->light.pos, intersection);
	shadow_factor = get_shadow_factor(data, intersection, data->light);
	diffuse = get_diffuse_lighting(data->light, normal, light_dir, object->color, shadow_factor, d_light);
	color.r = fmin(diffuse.r + ambient.r, 255.0);
    color.g = fmin(diffuse.g + ambient.g, 255.0);
    color.b = fmin(diffuse.b + ambient.b, 255.0);
	return (color);
}
