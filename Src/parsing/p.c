#include "miniRT.h"

int	validate_filename(const char *filename)
{
	const char	*extension;
	size_t		len;
	size_t		ext_len;

	extension = ".rt";
	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (len < ext_len)
	{
		ft_printf("Error: Invalid file extension. Expected .rt\n");
		return (1);
	}
	if (ft_strcmp((char *)(filename + len - ext_len), (char *)extension) != 0)
	{
		ft_printf("Error: Invalid file extension. Expected .rt\n");
		return (1);
	}
	return (0);
}

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

int	parse_ambient_color(char **color_split, t_data *data)
{
	if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
	{
		free_split(color_split);
		ft_printf("Error: Invalid ambient light color format\n");
		return (1);
	}
	data->ambient.color.r = ft_atoi(color_split[0]);
	data->ambient.color.g = ft_atoi(color_split[1]);
	data->ambient.color.b = ft_atoi(color_split[2]);
	return (0);
}

int	parse_ambient(char **split, t_data *data)
{
	char	**color_split;

	if (data->ambient.ratio != -1)
	{
		ft_printf("Error: Ambient light already defined\n");
		return (1);
	}
	if (!split[1] || !split[2])
	{
		ft_printf("Error: Invalid ambient light format\n");
		return (1);
	}
	color_split = ft_split(split[2], ',');
	if (parse_ambient_color(color_split, data))
		return (1);
	data->ambient.ratio = ft_atof(split[1]);
	free_split(color_split);
	return (0);
}

int	parse_camera_position(char **pos_split, t_data *data)
{
	if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2])
	{
		free_split(pos_split);
		ft_printf("Error: Invalid camera position format\n");
		return (1);
	}
	data->camera.pos.x = ft_atof(pos_split[0]);
	data->camera.pos.y = ft_atof(pos_split[1]);
	data->camera.pos.z = ft_atof(pos_split[2]);
	return (0);
}

int	parse_camera_orientation(char **orient_split, t_data *data)
{
	if (!orient_split || !orient_split[0] || !orient_split[1]
		|| !orient_split[2])
	{
		free_split(orient_split);
		ft_printf("Error: Invalid camera orientation format\n");
		return (1);
	}
	data->camera.orient.x = ft_atof(orient_split[0]);
	data->camera.orient.y = ft_atof(orient_split[1]);
	data->camera.orient.z = ft_atof(orient_split[2]);
	return (0);
}

int	parse_camera(char **split, t_data *data)
{
	char	**pos_split;
	char	**orient_split;
	int		result;

	if (data->camera.fov != -1)
	{
		ft_printf("Error: Camera already defined\n");
		return (1);
	}
	if (!split[1] || !split[2] || !split[3])
	{
		ft_printf("Error: Invalid camera format\n");
		return (1);
	}
	pos_split = ft_split(split[1], ',');
	orient_split = ft_split(split[2], ',');
	result = parse_camera_position(pos_split, data);
	result += parse_camera_orientation(orient_split, data);
	if (result > 0)
		return (free_split(pos_split), free_split(orient_split), 1);
	data->camera.fov = ft_atoi(split[3]);
	free_split(pos_split);
	free_split(orient_split);
	return (0);
}

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
