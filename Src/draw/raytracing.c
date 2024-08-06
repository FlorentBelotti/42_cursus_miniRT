/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:17:54 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/06 19:13:50 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static t_vector get_reference_up(t_data *data)
{
	t_vector ref_up;

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
	data->view_width = 2.0 * tan(data->camera.fov_rad / 2.0);
	data->view_height = data->view_width / aspect_ratio;
}

t_vector add(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return (result);
}

t_vector sub(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return (result);
}

t_vector mul(t_vector a, double b)
{
	t_vector	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;

	return (result);
}

static t_vector	get_ray_direction(t_data *data, int x, int y)
{
	t_vector	ray_dir;
	t_vector	pixel_pos;
	double		u;
	double		v;

    u = (2.0 * ((x + 0.5) / WINDOW_WIDTH) - 1.0) * data->view_width / 2.0;
    v = (2.0 * ((y + 0.5) / WINDOW_HEIGHT) - 1.0) * data->view_height / 2.0;
    pixel_pos = add(add(data->camera.pos, mul(data->camera.right, u)), mul(data->camera.up, v));
    pixel_pos = add(pixel_pos, data->camera.orient);
    ray_dir = sub(pixel_pos, data->camera.pos);
    normalize_vector(&ray_dir);
	return (ray_dir);
}

static int	check_for_intersections(t_object *object, t_data *data, t_ray *ray)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
	{
		d = sphere_intersection(data, &object->specific.sphere, &ray->direction, object);
	}
	else if (object->type == CYLINDER)
	{
		d = cylinder_intersection(data, &object->specific.cylinder, &ray->direction, object);
	}
	else if (object->type == PLANE)
	{
		d = plane_intersection(data, &object->specific.plane, &ray->direction);
	}
	return (d);
}

static void	render(t_data *data, t_ray *ray, int x, int y)
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

int	raytracing(t_data *data)
{
	t_ray ray;
	int	x;
	int	y;

	y = 0;
	get_camera_axis_and_viewing_plane(data);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			ray.direction = get_ray_direction(data, x, y);
			render(data, &ray, x, y);
			//printf("(%d, %d) ray.x : %f | ray.y : %f | ray.z : %f\n", x, y, ray.direction.x, ray.direction.y, ray.direction.z);
			x++;
		}
		y++;
	}
	return (0);
}
