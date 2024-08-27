/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 15:31:55 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/27 23:00:19 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

t_color	get_ambient_light(t_ambient ambient, t_color object_color)
{
	t_color	res;

	res.r = (int)(object_color.r * ambient.ratio * (ambient.color.r / 255.0));
	res.g = (int)(object_color.g * ambient.ratio * (ambient.color.g / 255.0));
	res.b = (int)(object_color.b * ambient.ratio * (ambient.color.b / 255.0));
	res.r = fmin(res.r, 255);
	res.g = fmin(res.g, 255);
	res.b = fmin(res.b, 255);
	return (res);
}
