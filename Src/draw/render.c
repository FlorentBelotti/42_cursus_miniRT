/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:40:28 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 03:00:02 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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
				if (current_object->type == SPHERE)
				{
					if (sphere_intersection(data, &current_object->specific.sphere, &data->rays[y * WINDOW_WIDTH + x].direction) == 1)
						ft_mlx_pixel_put(data->img, x, y);
				}
				else if (current_object->type == CYLINDER)
				{
					if (cylinder_intersection(data, &current_object->specific.cylinder, &data->rays[y * WINDOW_WIDTH + x].direction) == 1)
						ft_mlx_pixel_put(data->img, x, y);
				}
				else if (current_object->type == PLANE)
				{
					if (plane_intersection(data, &current_object->specific.plane, &data->rays[y * WINDOW_WIDTH + x].direction) == 1)
						ft_mlx_pixel_put(data->img, x, y);
				}
				current_object = current_object->next;
			}
			x++;
		}
		y++;
	}
	free(data->inter);
}
