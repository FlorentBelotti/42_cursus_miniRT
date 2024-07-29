/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 23:12:58 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static void	check_ray_intersection(t_object *object, t_data *data, int x, int y)
{
	if (object->type == SPHERE)
	{
		if (sphere_intersection(data, &object->specific.sphere,
			&data->rays[y * WINDOW_WIDTH + x].direction) == 1)
	}
	else if (object->type == CYLINDER)
	{
		if (cylinder_intersection(data, &object->specific.cylinder,
			&data->rays[y * WINDOW_WIDTH + x].direction) == 1)
			ft_mlx_pixel_put(data->img, x, y);
	}
	else if (object->type == PLANE)
	{
		if (plane_intersection(data, &object->specific.plane,
			&data->rays[y * WINDOW_WIDTH + x].direction) == 1)
			ft_mlx_pixel_put(data->img, x, y);
	}
}

void	render(t_data *data)
{
	t_object *current_object;
	int	x;
	int	y;

	y = 0;
	data->inter = malloc(sizeof(t_inter));
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			current_object = data->objects;
			while (current_object)
			{
				check_ray_intersection(current_object, data, x, y);
				current_object = current_object->next;
			}
			x++;
		}
		y++;
	}
	free(data->inter);
}
