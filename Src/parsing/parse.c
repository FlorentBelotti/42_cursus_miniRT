#include "miniRT.h"

char	*construct_scene_path(const char *filename)
{
	const char	*scene_dir;
	size_t		len;
	char		*filepath;

	scene_dir = "Scene/";
	len = ft_strlen(scene_dir) + ft_strlen(filename) + 1;
	filepath = malloc(len);
	if (filepath)
	{
		ft_strlcpy(filepath, scene_dir, len);
		ft_strlcat(filepath, filename, len);
	}
	return (filepath);
}

void	init_scene_data(t_data *data)
{
	data->ambient.ratio = -1;
	data->camera.fov = -1;
	data->light = NULL;
}

int	parse_scene_file(int fd, t_data *data)
{
	char	*line;
	int		result;

	result = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = parse_line(line, data);
		free(line);
		if (result)
			return (1);
		line = get_next_line(fd);
	}
	return (0);
}

int	check_mandatory_elements(t_data *data)
{
	if (data->ambient.ratio == -1 || data->camera.fov == -1
		|| data->light == NULL || data->light->brightness == -1)
	{
		ft_printf("Error: Missing mandatory scene elements\n");
		return (1);
	}
	return (0);
}

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

int	parse_sphere_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**color_split;

	pos_split = ft_split(split[1], ',');
	color_split = ft_split(split[3], ',');
	if (!pos_split || !color_split)
	{
		free_split(pos_split);
		free_split(color_split);
		ft_printf("Error: Invalid sphere format\n");
		free(obj);
		return (1);
	}
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	obj->specific.sphere.diameter = ft_atof(split[2]);
	free_split(pos_split);
	free_split(color_split);
	return (0);
}

int	parse_sphere(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (parse_sphere_data(split, obj))
		return (1);
	obj->type = SPHERE;
	if (parse_object_options(split, obj))
		return (1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

int	parse_plane_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**normal_split;
	char	**color_split;

	pos_split = ft_split(split[1], ',');
	normal_split = ft_split(split[2], ',');
	color_split = ft_split(split[3], ',');
	if (!pos_split || !normal_split || !color_split)
		return (free_split(pos_split), free_split(pos_split),
			free_split(normal_split), free_split(color_split),
			ft_printf("Error: Invalid plane format\n"), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.plane.normal.x = ft_atof(normal_split[0]);
	obj->specific.plane.normal.y = ft_atof(normal_split[1]);
	obj->specific.plane.normal.z = ft_atof(normal_split[2]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(normal_split);
	free_split(color_split);
	return (0);
}

int	parse_plane(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (parse_plane_data(split, obj))
		return (1);
	obj->type = PLANE;
	obj->checkerboard = false;
	ft_memset(&obj->noise, 0, sizeof(t_noise));
	if (parse_object_options(split, obj))
	{
		free(obj);
		return (1);
	}
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

int	parse_cylinder_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**axis_split;
	char	**color_split;

	pos_split = ft_split(split[1], ',');
	axis_split = ft_split(split[2], ',');
	color_split = ft_split(split[5], ',');
	if (!pos_split || !axis_split || !color_split)
		return (free_split(pos_split), free_split(axis_split),
			free_split(color_split),
			ft_printf("Error: Invalid cylinder format\n"), free(obj), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.cylinder.axis.x = ft_atof(axis_split[0]);
	obj->specific.cylinder.axis.y = ft_atof(axis_split[1]);
	obj->specific.cylinder.axis.z = ft_atof(axis_split[2]);
	obj->specific.cylinder.diameter = ft_atof(split[3]);
	obj->specific.cylinder.height = ft_atof(split[4]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(axis_split);
	return (free_split(color_split), 0);
}

int	parse_cylinder(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (parse_cylinder_data(split, obj))
		return (1);
	obj->type = CYLINDER;
	if (parse_object_options(split, obj))
		return (1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

int	parse_cone_data(char **split, t_object *obj)
{
	char	**pos_split;
	char	**axis_split;
	char	**color_split;

	pos_split = ft_split(split[1], ',');
	axis_split = ft_split(split[2], ',');
	color_split = ft_split(split[5], ',');
	if (!pos_split || !axis_split || !color_split)
		return (free_split(pos_split), free_split(axis_split),
			free_split(axis_split), free_split(color_split),
			ft_printf("Error: Invalid cone format\n"), free(obj), 1);
	obj->pos.x = ft_atof(pos_split[0]);
	obj->pos.y = ft_atof(pos_split[1]);
	obj->pos.z = ft_atof(pos_split[2]);
	obj->specific.cone.axis.x = ft_atof(axis_split[0]);
	obj->specific.cone.axis.y = ft_atof(axis_split[1]);
	obj->specific.cone.axis.z = ft_atof(axis_split[2]);
	obj->specific.cone.diameter = ft_atof(split[3]);
	obj->specific.cone.height = ft_atof(split[4]);
	obj->color.r = ft_atoi(color_split[0]);
	obj->color.g = ft_atoi(color_split[1]);
	obj->color.b = ft_atoi(color_split[2]);
	free_split(pos_split);
	free_split(axis_split);
	return (free_split(color_split), 0);
}

int	parse_cone(char **split, t_data *data)
{
	t_object	*obj;

	obj = malloc(sizeof(t_object));
	if (!obj)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	if (parse_cone_data(split, obj))
		return (1);
	obj->type = CONE;
	if (parse_object_options(split, obj))
		return (1);
	obj->next = data->objects;
	data->objects = obj;
	data->object_count++;
	return (0);
}

void	free_objects(t_object *objects)
{
	t_object	*tmp;

	while (objects)
	{
		tmp = objects;
		objects = objects->next;
		free(tmp);
	}
}

void	free_lights(t_light *lights)
{
	t_light	*tmp;

	while (lights)
	{
		tmp = lights;
		lights = lights->next;
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	if (data)
	{
		free_objects(data->objects);
		free_lights(data->light);
		if (data->img)
		{
			if (data->img->img_ptr)
				mlx_destroy_image(data->mlx, data->img->img_ptr);
			free(data->img);
		}
		if (data->window)
			mlx_destroy_window(data->mlx, data->window);
		if (data->mlx)
		{
			mlx_destroy_display(data->mlx);
			free(data->mlx);
		}
		free(data);
	}
}
