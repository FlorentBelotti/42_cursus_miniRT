/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:52:10 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/04 17:57:45 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static t_color	get_ambient_light(t_ambient ambient, t_color object_color)
{
	t_color	res;

	res.r = (int)(object_color.r * ambient.ratio * (ambient.color.r / 255.0));
	res.g = (int)(object_color.g * ambient.ratio * (ambient.color.g / 255.0));
	res.b = (int)(object_color.b * ambient.ratio * (ambient.color.b / 255.0));
	res.r = fmin(res.r, 255);
	res.g = fmin(res.g, 255);
	res.b = fmin(res.b, 255);
	return (res);
}

static t_color	get_diffuse_lighting(t_light *light, t_shadow *parts, t_color object_color)
{
	t_color	diffuse;
	double	intensity;
	double	dot;

	dot = get_scalar_product(&parts->normal, &parts->light_dir);
	intensity = fmax(0.0, dot) * light->brightness;
	if (parts->shadow_factor > 0 && parts->shadow_factor <= parts->d_light)
		intensity *= 0.5;
	diffuse.r = fmin(object_color.r * intensity * (light->color.r / 255.0), 255.0);
	diffuse.g = fmin(object_color.g * intensity * (light->color.g / 255.0), 255.0);
	diffuse.b = fmin(object_color.b * intensity * (light->color.b / 255.0), 255.0);
	return (diffuse);
}

static t_vector	get_object_normal(t_vector light_pos, t_vector intersection, t_object *object)
{
	t_vector	normal;
	t_vector	oc;
	t_vector	projection;

	(void)light_pos;
	if (object->type == SPHERE)
		normal = sub(intersection, object->pos);
	else if (object->type == PLANE)
		normal = object->specific.plane.normal;
	else if (object->type == CYLINDER)
	{
		if (object->specific.cylinder.disk > 0)
			normal = get_closest_cap_normal(&object->specific.cylinder, object, intersection);
		else
		{
			oc = sub(intersection, object->pos);
			projection = mul(object->specific.cylinder.axis, get_scalar_product(&oc, &object->specific.cylinder.axis));
			normal = sub(oc, projection);
		}
	}
	normalize_vector(&normal);
	return (normal);
}


static	t_color get_specular_lighting(t_light *light, t_shadow *parts, t_vector view_dir, double shininess)
{
	t_color specular;
	t_vector reflect_dir;
	double spec_intensity;
	double spec_dot;

	reflect_dir = sub(mul(parts->normal, 2.0 * get_scalar_product(&parts->light_dir, &parts->normal)), parts->light_dir);
	normalize_vector(&reflect_dir);
	spec_dot = get_scalar_product(&reflect_dir, &view_dir);
	spec_intensity = pow(fmax(0.0, spec_dot), shininess) * light->brightness;
	specular.r = fmin(spec_intensity * (light->color.r / 255.0) * 255.0, 255.0);
	specular.g = fmin(spec_intensity * (light->color.g / 255.0) * 255.0, 255.0);
	specular.b = fmin(spec_intensity * (light->color.b / 255.0) * 255.0, 255.0);
	return (specular);
}

t_color	get_pixel_lighting(t_data *data, t_object *object, t_vector intersection)
{
	t_shadow	parts;
	t_vector	view_dir;
	t_light		*current_light;
	double		shininess = 32.0;

	view_dir = sub(data->camera.pos, intersection);
	normalize_vector(&view_dir);
	parts.ambient = get_ambient_light(data->ambient, object->color);
	parts.color = parts.ambient;
	current_light = data->light;
	while (current_light)
	{
		parts.light_dir = sub(current_light->pos, intersection);
		normalize_vector(&parts.light_dir);
		parts.normal = get_object_normal(current_light->pos, intersection, object);
		parts.d_light = get_light_distance(current_light->pos, intersection);
		parts.shadow_factor = get_shadow_factor(data, intersection, current_light);
		parts.diffuse = get_diffuse_lighting(current_light, &parts, object->color);
		parts.specular = get_specular_lighting(current_light, &parts, view_dir, shininess);
		parts.color.r = fmin(parts.color.r + parts.diffuse.r + parts.specular.r, 255.0);
		parts.color.g = fmin(parts.color.g + parts.diffuse.g + parts.specular.g, 255.0);
		parts.color.b = fmin(parts.color.b + parts.diffuse.b + parts.specular.b, 255.0);
		current_light = current_light->next;
	}
	return (parts.color);
}
