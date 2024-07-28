/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:54 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/28 18:52:48 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

/* static void	free_rays(t_data *data)
{
	free(data->rays);
	data->rays = NULL;
}*/

static int	create_rays(t_data *data)
{
	data->total_rays = WINDOW_HEIGHT * WINDOW_WIDTH;
	data->rays = (t_ray *)malloc(data->total_rays * sizeof(t_ray));
	if (data->rays == NULL)
		return (1);
	return (0);
}

static void	get_ray_direction(t_data *data, int x, int y)
{
	t_vector	ray_dir;
	//double		length;

	ray_dir.x = (x - (WINDOW_WIDTH / 2)) - data->camera.pos.x;
	ray_dir.y = (y - (WINDOW_HEIGHT / 2)) - data->camera.pos.y;
	ray_dir.z = (data->farthest_object + 1) - data->camera.pos.z;
	/*length = sqrt(ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z);
	ray_dir.x /= length;
	ray_dir.y /= length;
	ray_dir.z /= length;*/
	data->rays[y * WINDOW_WIDTH + x].direction = ray_dir;
}

/*void print_rays(t_data *data)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < 2; x++) { // Limite à 2 rayons par ligne
            int i = y * WINDOW_WIDTH + x;
            t_ray ray = data->rays[i];
            printf("Ray [%d, %d] -> Direction: (x: %.2f, y: %.2f, z: %.2f)\n",
                   x, y, ray.direction.x, ray.direction.y, ray.direction.z);
        }
    }
}*/

int	raytracing(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	//printf("fartest point : %d\n", data->farthest_object);
	if (create_rays(data) == 1)
		return (1);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			get_ray_direction(data, x, y);

			// DEBUG TO SUPPRESS

			t_object *current_object = data->objects;
			while (current_object)
			{
				if (current_object->type == SPHERE)
				{
					if (sphere_intersection(data, &current_object->specific.sphere, &data->rays[y * WINDOW_WIDTH + x].direction))
						printf("FOUND intersection at pixel (%d, %d)\n", x, y);
				}
				current_object = current_object->next;
			}

			//DEBUG END

			x++;
		}
		y++;
	}
	//print_rays(data);
	return (0);
}
