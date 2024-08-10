/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/10 17:31:14 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	check_for_intersections(t_object *object, t_data *data, t_ray *ray)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
		d = sphere_intersection(data, &object->specific.sphere,
				&ray->direction, object);
	else if (object->type == CYLINDER)
		d = cylinder_intersection(data, &object->specific.cylinder,
				&ray->direction, object);
	else if (object->type == PLANE)
		d = plane_intersection(data, &object->specific.plane,
				&ray->direction, object);
	return (d);
}

/*t_object	*choose_priority_object(t_object *old, t_object *current)
{
	if (old->type == current->type)
		return (current);
	else if (old->type < current->type)
		return (old);
	else
		return (current);
}*/

void	render(t_data *data, t_ray *ray, int x, int y)
{
	t_object	*current_object;
	t_object	*closest_object;
	//t_object	*old_object;
	double		d;

	current_object = data->objects;
	closest_object = NULL;
	while (current_object)
	{
		d = check_for_intersections(current_object, data, ray);
		if (d >= EPSILON && d < data->z_buffer[y][x])
		{
			closest_object = current_object;
			data->z_buffer[y][x] = d;
		}
		/*else if (d == data->z_buffer[y][x])
			closest_object = choose_priority_object(old_object, current_object);
		old_object = current_object;*/
		current_object = current_object->next;
	}
	if (closest_object)
		ft_mlx_pixel_put(data->img, x, y, rgb_to_int(closest_object->color));
}
