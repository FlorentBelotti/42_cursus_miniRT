/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:24 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:25 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_scene(const char *filename, t_data *data)
{
	char	*filepath;
	int		fd;
	int		result;

	filepath = construct_scene_path(filename);
	fd = open(filepath, O_RDONLY);
	free(filepath);
	if (fd < 0)
	{
		ft_printf("Error: Unable to open file %s\n", filename);
		return (1);
	}
	init_scene_data(data);
	result = parse_scene_file(fd, data);
	if (result == 0)
		result = check_mandatory_elements(data);
	close(fd);
	return (result);
}

int	parse_known_object(char **split, t_data *data)
{
	if (ft_strcmp(split[0], "A") == 0)
		return (parse_ambient(split, data));
	if (ft_strcmp(split[0], "C") == 0)
		return (parse_camera(split, data));
	if (ft_strcmp(split[0], "L") == 0)
		return (parse_light(split, data));
	if (ft_strcmp(split[0], "sp") == 0)
		return (parse_sphere(split, data));
	if (ft_strcmp(split[0], "pl") == 0)
		return (parse_plane(split, data));
	if (ft_strcmp(split[0], "cy") == 0)
		return (parse_cylinder(split, data));
	if (ft_strcmp(split[0], "co") == 0)
		return (parse_cone(split, data));
	return (-1);
}

int	parse_line(char *line, t_data *data)
{
	char	**split;
	int		result;

	split = ft_split(line, ' ');
	if (!split)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (!split[0])
	{
		free_split(split);
		return (0);
	}
	result = parse_known_object(split, data);
	if (result == -1)
	{
		ft_printf("Error: Unknown object type '%s'\n", split[0]);
		free_split(split);
		return (1);
	}
	free_split(split);
	return (result);
}

int	parse_object_options(char **split, t_object *obj)
{
	int	i;

	i = 4;
	while (split[i] != NULL)
	{
		if (ft_strcmp(split[i], "checkerboard") == 0 || ft_strcmp(split[i],
				"checkerboard\n") == 0)
		{
			obj->checkerboard = true;
		}
		else if (ft_strcmp(split[i], "P") == 0)
		{
			if (!split[i + 1] || !split[i + 2] || !split[i + 3] || !split[i
					+ 4])
				return (ft_printf("Error: Invalid Perlin noise format\n"), 1);
			obj->noise.octaves = ft_atoi(split[i + 1]);
			obj->noise.frequency = ft_atof(split[i + 2]);
			obj->noise.persistence = ft_atof(split[i + 3]);
			obj->noise.intensity = ft_atof(split[i + 4]);
			i += 4;
		}
		i++;
	}
	return (0);
}

int	parse_perlin_noise(char **split, t_noise *noise)
{
	if (!split[1] || !split[2] || !split[3] || !split[4])
	{
		ft_printf("Error: Invalid Perlin noise format\n");
		return (1);
	}
	noise->octaves = ft_atoi(split[1]);
	noise->frequency = ft_atof(split[2]);
	noise->persistence = ft_atof(split[3]);
	noise->intensity = ft_atof(split[4]);
	return (0);
}
