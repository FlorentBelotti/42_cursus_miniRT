/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:57:09 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 15:46:36 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static void	init_checker(t_checker *checker)
{
	checker->black.r = 0;
	checker->black.g = 0;
	checker->black.b = 0;
	checker->white.r = 255;
	checker->white.g = 255;
	checker->white.b = 255;
	checker->scale = 5.0;
}

t_color	apply_checkerboard_pattern(t_object *object, t_vector inter)
{
	t_checker	checker;

	init_checker(&checker);
	if (object->type == PLANE)
	{
		if (fabs(object->specific.plane.normal.y)
			> fabs(object->specific.plane.normal.x))
			return (apply_smooth_checkerboard_to_plane(inter, &checker));
		else
			return (apply_checkerboard_to_vertical_plane(inter, &checker));
	}
	else if (object->type == SPHERE)
		return (apply_checkerboard_to_sphere(object, inter, &checker));
	else if (object->type == CYLINDER)
		return (apply_checkerboard_to_cylinder(object, inter, &checker));
	else if (object->type == CONE)
		return (apply_checkerboard_to_cone(object, inter, &checker));
	return (object->color);
}
