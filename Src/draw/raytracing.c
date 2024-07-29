/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:54 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/30 00:43:20 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

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
	double		length;

	ray_dir.x = (x - (WINDOW_WIDTH / 2)) - data->camera.pos.x;
	ray_dir.y = (y - (WINDOW_HEIGHT / 2))  - data->camera.pos.y;
	ray_dir.z = WINDOW_WIDTH / (2 * tan(data->camera.fov / 2))  - data->camera.pos.z;
	length = sqrt(ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z);
	ray_dir.x /= length;
	ray_dir.y /= length;
	ray_dir.z /= length;
	data->rays[y * WINDOW_WIDTH + x].direction = ray_dir;
}

int	raytracing(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	if (create_rays(data) == 1)
		return (1);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			get_ray_direction(data, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
