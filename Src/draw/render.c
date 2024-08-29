/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/29 00:14:49 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void	render(t_data *data, t_ray *ray, int x, int y)
{
	t_object	*current_object;
	t_object	*closest_object;
	t_vector	intersection;
	t_color		color;
	double		d;

	current_object = data->objects;
	closest_object = NULL;
	while (current_object)
	{
		d = get_intersection_distance(current_object, ray, -1);
		if (d >= EPSILON && d < data->z_buffer[y][x])
		{
			closest_object = current_object;
			data->z_buffer[y][x] = d;
		}
		current_object = current_object->next;
	}
	if (closest_object)
	{
		d = get_intersection_distance(closest_object, ray, -1);
		intersection = add(ray->origin, mul(ray->direction, d));
		color = get_pixel_lighting(data, closest_object, intersection);
		ft_mlx_pixel_put(data->img, x, y, rgb_to_int(color));
	}
}
