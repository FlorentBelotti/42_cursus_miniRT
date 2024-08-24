/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/23 17:51:15 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

/* static t_object	*choose_priority_object(t_object *old, t_object *current)
{
	if (old->type == current->type)
		return (current);
	else if (old->type < current->type)
		return (old);
	else
		return (current);
}

else if (d == data->z_buffer[y][x])
	closest_object = choose_priority_object(old_object, current_object);
old_object = current_object; */

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
		d = check_for_intersections(current_object, ray);
		if (d >= EPSILON && d < data->z_buffer[y][x])
		{
			closest_object = current_object;
			data->z_buffer[y][x] = d;
			intersection = add(data->camera.pos, mul(ray->direction, d));
		}
		current_object = current_object->next;
	}
	if (closest_object)
	{
		color = get_pixel_lightning(data, closest_object, intersection);
		ft_mlx_pixel_put(data->img, x, y, rgb_to_int(color));
	}
}
