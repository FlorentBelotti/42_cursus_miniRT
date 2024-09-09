/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:21 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:22 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_light_position(char **pos_split, t_light *new_light)
{
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2])
	{
		free_split(pos_split);
		ft_printf("Error: Invalid light position format\n");
		return (1);
	}
	new_light->pos.x = ft_atof(pos_split[0]);
	new_light->pos.y = ft_atof(pos_split[1]);
	new_light->pos.z = ft_atof(pos_split[2]);
	return (0);
}

int	parse_light_color(char **color_split, t_light *new_light)
{
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
	{
		free_split(color_split);
		ft_printf("Error: Invalid light color format\n");
		return (1);
	}
	new_light->color.r = ft_atoi(color_split[0]);
	new_light->color.g = ft_atoi(color_split[1]);
	new_light->color.b = ft_atoi(color_split[2]);
	return (0);
}

void	add_light_to_list(t_data *data, t_light *new_light)
{
	t_light	*current;

	if (data->light == NULL)
	{
		data->light = new_light;
	}
	else
	{
		current = data->light;
		while (current->next)
		{
			current = current->next;
		}
		current->next = new_light;
	}
}

int	parse_light(char **split, t_data *data)
{
	t_light	*new_light;
	char	**pos_split;
	char	**color_split;
	int		result;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
		return (ft_printf("Error: Memory allocation failed\n"), 1);
	if (!split[1] || !split[2] || !split[3])
		return (ft_printf("Error: Invalid light format\n"), free(new_light), 1);
	pos_split = ft_split(split[1], ',');
	color_split = ft_split(split[3], ',');
	result = parse_light_position(pos_split, new_light);
	result += parse_light_color(color_split, new_light);
	if (result > 0)
		return (free(new_light), 1);
	new_light->brightness = ft_atof(split[2]);
	new_light->next = NULL;
	free_split(pos_split);
	free_split(color_split);
	add_light_to_list(data, new_light);
	return (0);
}
