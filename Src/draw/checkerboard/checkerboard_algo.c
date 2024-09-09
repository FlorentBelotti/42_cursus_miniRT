/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_algo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:38:29 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:10:55 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_color	apply_smooth_checkerboard_to_plane(t_vector inter, t_checker *checker)
{
	int		check_x;
	int		check_z;

	checker->scale = 1.0;
	check_x = (int)(floor(inter.x * checker->scale));
	check_z = (int)(floor(inter.z * checker->scale));
	if ((check_x + check_z) % 2 == 0)
		return (checker->white);
	else
		return (checker->black);
}

t_color	apply_checkerboard_to_vertical_plane(t_vector inter, t_checker *checker)
{
	int		check_y;
	int		check_z;

	checker->scale = 1.0;
	check_y = (int)(floor(inter.y * checker->scale));
	check_z = (int)(floor(inter.z * checker->scale));
	if ((check_y + check_z) % 2 == 0)
		return (checker->white);
	else
		return (checker->black);
}

t_color	apply_checkerboard_to_sphere(t_object *object,
		t_vector inter, t_checker *checker)
{
	double		u;
	double		v;
	int			check_u;
	int			check_v;

	checker->relative_pos = sub(inter, object->pos);
	u = 0.5 + atan2(checker->relative_pos.z,
			checker->relative_pos.x) / (2 * M_PI);
	v = 0.5 - asin(checker->relative_pos.y / object->specific.sphere.diameter)
		/ M_PI;
	check_u = (int)(floor(u * 10.0));
	check_v = (int)(floor(v * 10.0));
	if ((check_u + check_v) % 2 == 0)
		return (checker->white);
	else
		return (checker->black);
}

t_color	apply_checkerboard_to_cylinder(t_object *object,
		t_vector inter, t_checker *checker)
{
	int	t;
	int	h;

	checker->relative_pos = sub(inter, object->pos);
	if (fabs(object->specific.cylinder.axis.y) > 0.9)
	{
		checker->theta = atan2(checker->relative_pos.z,
				checker->relative_pos.x);
		checker->height = checker->relative_pos.y;
	}
	else
	{
		checker->theta = atan2(checker->relative_pos.y,
				checker->relative_pos.z);
		checker->height = checker->relative_pos.x;
	}
	t = (int)(floor(checker->theta * checker->scale));
	h = (int)(floor(checker->height * checker->scale));
	if ((t + h) % 2 == 0)
		return (checker->white);
	else
		return (checker->black);
}

t_color	apply_checkerboard_to_cone(t_object *object,
		t_vector inter, t_checker *checker)
{
	int	t;
	int	h;

	checker->relative_pos = sub(inter, object->pos);
	if (fabs(object->specific.cone.axis.y) > 0.9)
	{
		checker->theta = atan2(checker->relative_pos.z,
				checker->relative_pos.x);
		checker->height = checker->relative_pos.y;
	}
	else
	{
		checker->theta = atan2(checker->relative_pos.y,
				checker->relative_pos.z);
		checker->height = checker->relative_pos.x;
	}
	t = (int)(floor(checker->theta * checker->scale));
	h = (int)(floor(checker->height * checker->scale));
	if ((t + h) % 2 == 0)
		return (checker->white);
	else
		return (checker->black);
}
