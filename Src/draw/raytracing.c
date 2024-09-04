/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:54 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/05 00:35:47 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static t_vector	get_reference_up(t_data *data)
{
	t_vector	ref_up;

	ref_up.x = 0.0;
	if (fabs(data->camera.orient.y) == 1.0)
	{
		ref_up.y = 0.0;
		ref_up.z = 1.0;
		return (ref_up);
	}
	else
	{
		ref_up.y = 1.0;
		ref_up.z = 0.0;
		return (ref_up);
	}
}

static void	get_camera_axis_and_viewing_plane(t_data *data)
{
	t_vector	ref_up;
	double		aspect_ratio;

	ref_up = get_reference_up(data);
	data->camera.right = vector_cross(data->camera.orient, ref_up);
	normalize_vector(&data->camera.right);
	data->camera.up = vector_cross(data->camera.right, data->camera.orient);
	normalize_vector(&data->camera.up);
	data->camera.fov_rad = data->camera.fov * (M_PI / 180.0);
	aspect_ratio = (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT;
	data->view_width = tan(data->camera.fov_rad / 2.0);
	data->view_height = data->view_width / aspect_ratio;
}

static t_vector	get_ray_direction(t_data *data, int x, int y)
{
	t_vector	ray_dir;
	t_vector	pixel_pos;
	double		u;
	double		v;

	u = -(2.0 * ((x + 0.5) / WINDOW_WIDTH) - 1.0) * data->view_width;
	v = (1.0 - 2.0 * ((y + 0.5) / WINDOW_HEIGHT)) * data->view_height;
	pixel_pos = add(add(data->camera.pos, mul(data->camera.right, u)),
			mul(data->camera.up, v));
	pixel_pos = add(pixel_pos, data->camera.orient);
	ray_dir = sub(pixel_pos, data->camera.pos);
	normalize_vector(&ray_dir);
	return (ray_dir);
}

int	raytracing(t_data *data)
{
	t_ray	ray;
	int		x;
	int		y;

	y = 0;
	get_camera_axis_and_viewing_plane(data);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			data->z_buffer[y][x] = DBL_MAX;
			ray.direction = get_ray_direction(data, x, y);
			ray.origin = data->camera.pos;
			render(data, &ray, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
