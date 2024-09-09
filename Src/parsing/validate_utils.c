/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:34 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:35 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	validate_color(t_color color)
{
	int	is_valid;

	is_valid = 1;
	if (color.r < 0 || color.r > 255)
		is_valid = 0;
	if (color.g < 0 || color.g > 255)
		is_valid = 0;
	if (color.b < 0 || color.b > 255)
		is_valid = 0;
	if (!is_valid)
	{
		ft_printf("Error: Color values must be in the range [0, 255]\n");
		return (1);
	}
	return (0);
}

int	validate_ambient(t_data *data)
{
	if (data->ambient.ratio == -1)
	{
		ft_printf("Error: Ambient light not defined\n");
		return (1);
	}
	return (0);
}

int	validate_camera(t_data *data)
{
	if (data->camera.fov == -1)
	{
		ft_printf("Error: Camera not defined\n");
		return (1);
	}
	return (0);
}

int	validate_light(t_data *data)
{
	if (data->light->brightness == -1)
	{
		ft_printf("Error: Light not defined\n");
		return (1);
	}
	return (0);
}

int	validate_scene_elements(t_data *data)
{
	int	result;

	result = 0;
	result += validate_ambient(data);
	result += validate_camera(data);
	result += validate_light(data);
	if (result > 0)
		return (1);
	return (0);
}
