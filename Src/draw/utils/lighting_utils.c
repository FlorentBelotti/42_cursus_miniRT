/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:40:46 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 17:00:26 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_color	get_ambient_light(t_ambient ambient, t_color object_color)
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

void	init_lighting(t_shadow *parts, t_data *data, t_object *object,
		t_vector intersection)
{
	parts->view_dir = sub(data->camera.pos, intersection);
	parts->shininess = 32.0;
	normalize_vector(&parts->view_dir);
	parts->ambient = get_ambient_light(data->ambient, object->color);
	parts->color = parts->ambient;
}

void	add_color(t_shadow *parts)
{
	parts->color.r = fmin(parts->color.r + parts->diffuse.r
			+ parts->specular.r, 255.0);
	parts->color.g = fmin(parts->color.g + parts->diffuse.g
			+ parts->specular.g, 255.0);
	parts->color.b = fmin(parts->color.b + parts->diffuse.b
			+ parts->specular.b, 255.0);
}
