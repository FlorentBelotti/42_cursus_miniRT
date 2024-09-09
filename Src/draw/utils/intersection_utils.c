/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42perpignan.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:02:48 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 16:08:31 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static double	get_highest_intersection(t_inter *inter,
		double closest_intersection)
{
	if (inter->P1_proj >= inter->c_min && inter->P1_proj <= inter->c_max
		&& inter->r1 > EPSILON)
		closest_intersection = inter->r1;
	if (inter->P2_proj >= inter->c_min && inter->P2_proj <= inter->c_max
		&& inter->r2 > EPSILON)
	{
		if (closest_intersection == -1 || inter->r2 > closest_intersection)
			closest_intersection = inter->r2;
	}
	return (closest_intersection);
}

static double	get_lowest_intersection(t_inter *inter,
		double closest_intersection)
{
	if (inter->P1_proj >= inter->c_min && inter->P1_proj <= inter->c_max
		&& inter->r1 > EPSILON)
		closest_intersection = inter->r1;
	if (inter->P2_proj >= inter->c_min && inter->P2_proj <= inter->c_max
		&& inter->r2 > EPSILON)
	{
		if (closest_intersection == -1 || inter->r2 < closest_intersection)
			closest_intersection = inter->r2;
	}
	return (closest_intersection);
}

double	c_return_high_or_low(t_inter *inter, int code)
{
	double	closest_intersection;

	closest_intersection = -1;
	if (code == 1)
		return (get_highest_intersection(inter, closest_intersection));
	else
		return (get_lowest_intersection(inter, closest_intersection));
	return (closest_intersection);
}
