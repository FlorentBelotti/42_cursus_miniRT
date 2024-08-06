/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/06 19:27:19 by fbelotti         ###   ########.fr       */
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
				&ray->direction);
	return (d);
}

void	render(t_data *data, t_ray *ray, int x, int y)
{
	t_object	*current;
	t_object	*closest;
	double		d_min;
	double		d;

	d_min = -1;
	current = data->objects;
	closest = NULL;
	while (current)
	{
		d = check_for_intersections(current, data, ray);
		if (d > 0 && (d <= d_min || d_min == -1))
		{
			d_min = d;
			closest = current;
		}
		current = current->next;
	}
	if (closest)
		ft_mlx_pixel_put(data->img, x, y, rgb_to_int(closest->color));
}
