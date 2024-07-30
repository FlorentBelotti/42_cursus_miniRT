/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/30 18:05:58 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	check_ray_intersection(t_object *object, t_data *data, int x, int y)
{
	double	distance;

	distance = -1;
	if (object->type == SPHERE)
	{
		distance = sphere_intersection(data, &object->specific.sphere,
			&data->rays[y * WINDOW_WIDTH + x].direction);
		printf("(%d, %d) \t| SPHERE \t| distance : %f\n", x, y, distance);
	}
	else if (object->type == CYLINDER)
	{
		distance = cylinder_intersection(data, &object->specific.cylinder,
			&data->rays[y * WINDOW_WIDTH + x].direction);
		printf("(%d, %d) \t| CYLINDER \t| distance : %f\n", x, y, distance);
	}
	else if (object->type == PLANE)
	{
		distance = plane_intersection(data, &object->specific.plane,
			&data->rays[y * WINDOW_WIDTH + x].direction);
		printf("(%d, %d) \t| PLANE \t| distance : %f\n", x, y, distance);
	}
	return (distance);
}

void	render(t_data *data)
{
	t_object	*current_object;
	t_object	*closest_object;
	double		distance_min;
	double		distance;
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
			closest_object = NULL;
			distance_min = -1;
			while (current_object)
			{
				distance = check_ray_intersection(current_object, data, x, y);
				if (distance > 0 && (distance < distance_min || distance_min == -1))
				{
					distance_min = distance;
					closest_object = current_object;
				}
				current_object = current_object->next;
			}
			if (closest_object)
				ft_mlx_pixel_put(data->img, x, y, rgb_to_int(closest_object->color));
			x++;
		}
		y++;
	}
	free(data->inter);
}
