/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:25:59 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/29 18:42:33 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	get_light_distance(t_vector a, t_vector b)
{
	t_vector	diff;
	double		result;

	diff = sub(a, b);
	result = sqrt(get_scalar_product(&diff, &diff));
	return (result);
}

int	get_shadow_factor(t_data *data, t_vector intersection, t_light light)
{
	t_ray		shadow_ray;
	t_object	*current_object;
	double		d;
	double		d_light;
	double		shadow_factor;

	shadow_factor = -1.0;
	shadow_ray.direction = sub(light.pos, intersection);
	normalize_vector(&shadow_ray.direction);
	shadow_ray.origin = add(intersection, mul(shadow_ray.direction, EPSILON));
	d_light = get_light_distance(light.pos, shadow_ray.origin);
	current_object = data->objects;
	while (current_object)
	{
		d = get_intersection_distance(current_object, &shadow_ray, 1);
		if (d > EPSILON && d < d_light - EPSILON)
		{
			if (shadow_factor < 0 || d < shadow_factor)
				shadow_factor = d;
		}
		current_object = current_object->next;
	}
	return (shadow_factor);
}
