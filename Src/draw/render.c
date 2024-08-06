/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/06 13:36:27 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

/*static int	check_ray_intersection(t_object *object, t_data *data, int x, int y)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
	{
		d = sphere_intersection(data, &object->specific.sphere,
			&data->rays[y * WINDOW_WIDTH + x].direction);
	}
	else if (object->type == CYLINDER)
	{
		d = cylinder_intersection(data, &object->specific.cylinder,
			&data->rays[y * WINDOW_WIDTH + x].direction);
	}
	else if (object->type == PLANE)
	{
		d = plane_intersection(data, &object->specific.plane,
			&data->rays[y * WINDOW_WIDTH + x].direction);
	}
	return (d);
}

void	render(t_data *data)
{
	t_object	*current_object;
	t_object	*closest;
	double		d_min;
	double		d;
	int			x;
	int			y;

	y = 0;
	data->inter = malloc(sizeof(t_inter));
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			current_object = data->objects;
			closest = NULL;
			d_min = -1;
			while (current_object)
			{
				d = check_ray_intersection(current_object, data, x, y);
				if (d > 0 && (d <= d_min || d_min == -1))
				{
					d_min = d;
					closest = current_object;
				}
				current_object = current_object->next;
			}
			if (closest)
				ft_mlx_pixel_put(data->img, x, y, rgb_to_int(closest->color));
			x++;
		}
		y++;
	}
	free(data->inter);
}*/
