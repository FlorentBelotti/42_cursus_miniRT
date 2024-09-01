/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 18:33:02 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/01 18:40:40 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static void	rotate_camera_y(t_vector *orient, double angle)
{
	double new_orient_x;
	double new_orient_z;

	new_orient_x = orient->x * cos(angle) - orient->z * sin(angle);
	new_orient_z = orient->x * sin(angle) + orient->z * cos(angle);
	orient->x = new_orient_x;
	orient->z = new_orient_z;
}

static void	rotate_camera_x(t_vector *orient, double angle)
{
	double new_orient_y;
	double new_orient_z;

	new_orient_y = orient->y * cos(angle) - orient->z * sin(angle);
	new_orient_z = orient->y * sin(angle) + orient->z * cos(angle);
	orient->y = new_orient_y;
	orient->z = new_orient_z;
}

static void	apply_translation_to_camera(t_vector *v1, t_vector *v2, int code)
{
	if (code == 0)
	{
		v1->x -= v2->x * 1.0;
		v1->y -= v2->y * 1.0;
		v1->z -= v2->z * 1.0;
	}
	else if (code == 1)
	{
		v1->x += v2->x * 1.0;
		v1->y += v2->y * 1.0;
		v1->z += v2->z * 1.0;
	}
}

void	apply_movement_to_camera(int key_code, t_data *data)
{
	t_vector right_vector;
	t_vector up_vector;

	up_vector.x = 0.0;
	up_vector.y = 1.0;
	up_vector.z = 0.0;
	right_vector = vector_cross(data->camera.orient, up_vector);
	normalize_vector(&right_vector);
	up_vector = vector_cross(right_vector, data->camera.orient);
	normalize_vector(&up_vector);
	if (key_code == KEY_W)
		apply_translation_to_camera(&data->camera.pos, &data->camera.orient, 1);
	else if (key_code == KEY_S)
		apply_translation_to_camera(&data->camera.pos, &data->camera.orient, 0);
	else if (key_code == KEY_A)
		apply_translation_to_camera(&data->camera.pos, &right_vector, 1);
	else if (key_code == KEY_D)
		apply_translation_to_camera(&data->camera.pos, &right_vector, 0);
	else if (key_code == KEY_E)
		apply_translation_to_camera(&data->camera.pos, &up_vector, 1);
	else if (key_code == KEY_Q)
		apply_translation_to_camera(&data->camera.pos, &up_vector, 0);
	update_draw(data);
}

void	apply_rotation_to_camera(int key_code, t_data *data)
{
	double	rotation_angle;

	rotation_angle = M_PI / 36;
	if (key_code == KEY_LEFT)
		rotate_camera_y(&data->camera.orient, rotation_angle);
	else if (key_code == KEY_RIGHT)
		rotate_camera_y(&data->camera.orient, -rotation_angle);
	else if (key_code == KEY_UP)
		rotate_camera_x(&data->camera.orient, -rotation_angle);
	else if (key_code == KEY_DOWN)
		rotate_camera_x(&data->camera.orient, rotation_angle);
	update_draw(data);
}
