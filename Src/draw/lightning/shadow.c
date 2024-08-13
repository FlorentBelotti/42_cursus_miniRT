/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:25:59 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/13 15:56:34 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	get_light_distance(t_vector a, t_vector b)
{
	t_vector	diff;
	double		result;

	diff = sub(a, b);
	result = sqrt(get_scalar_product(&diff, &diff));
	return (result);
}

int	is_in_shadow(t_data *data, t_vector intersection, t_light light)
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
