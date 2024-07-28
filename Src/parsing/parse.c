#include "miniRT.h"

int validate_filename(const char *filename)
{
    const char *extension = ".rt";
    size_t len = ft_strlen(filename);
    size_t ext_len = ft_strlen(extension);

    if (len < ext_len || ft_strcmp((char *)(filename + len - ext_len), (char *)extension) != 0)
        return (ft_printf("Error: Invalid file extension. Expected .rt\n"), 1);
    return 0;
}

int validate_color(t_color color)
{
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255 || color.b < 0 || color.b > 255)
    {
        ft_printf("Error: Color values must be in the range [0, 255]\n");
        return 1;
    }
    return 0;
}

int validate_scene_elements(t_data *data)
{
    if (data->ambient.ratio == -1)
    {
        ft_printf("Error: Ambient light not defined\n");
        return 1;
    }
    if (data->camera.fov == -1)
    {
        ft_printf("Error: Camera not defined\n");
        return 1;
    }
    if (data->light.brightness == -1)
    {
        ft_printf("Error: Light not defined\n");
        return 1;
    }
    return 0;
}

#include "miniRT.h"

int parse_scene(const char *filename, t_data *data)
{
    if (validate_filename(filename) != 0)
        return 1;

    char *filepath = construct_scene_path(filename);
    int fd = open(filepath, O_RDONLY);
    free(filepath);
    if (fd < 0)
        return (ft_printf("Error: Unable to open file %s\n", filename), 1);

    char *line;
    data->ambient.ratio = -1;
    data->camera.fov = -1;
    data->light.brightness = -1;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (parse_line(line, data))
        {
            free(line);
            close(fd);
            return 1;
        }
        free(line);
    }
    close(fd);

    if (data->ambient.ratio == -1 || data->camera.fov == -1 || data->light.brightness == -1)
        return (ft_printf("Error: Missing mandatory scene elements\n"), 1);

    // Find the farthest object
    t_object *obj = data->objects;
	data->farthest_object = 0;
    while (obj)
    {
        if (obj->pos.z > data->farthest_object)
            data->farthest_object = obj->pos.z;
        obj = obj->next;
    }

    return 0;
}

int parse_ambient(char **split, t_data *data)
{
    if (data->ambient.ratio != -1)
        return (ft_printf("Error: Ambient light already defined\n"), 1);
    if (!split[1] || !split[2])
        return (ft_printf("Error: Invalid ambient light format\n"), 1);

    char **color_split = ft_split(split[2], ',');
    if (!color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(color_split);
        return (ft_printf("Error: Invalid ambient light color format\n"), 1);
    }

    data->ambient.ratio = ft_atof(split[1]);
    data->ambient.color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};
    free_split(color_split);

    if (validate_color(data->ambient.color))
        return 1;

    return 0;
}

int parse_camera(char **split, t_data *data)
{
    if (data->camera.fov != -1)
        return (ft_printf("Error: Camera already defined\n"), 1);
    if (!split[1] || !split[2] || !split[3])
        return (ft_printf("Error: Invalid camera format\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **orient_split = ft_split(split[2], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !orient_split || !orient_split[0] || !orient_split[1] || !orient_split[2])
    {
        free_split(pos_split);
        free_split(orient_split);
        return (ft_printf("Error: Invalid camera position or orientation format\n"), 1);
    }

    data->camera.pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    data->camera.orient = (t_vector){ft_atof(orient_split[0]), ft_atof(orient_split[1]), ft_atof(orient_split[2])};
    data->camera.fov = ft_atoi(split[3]);

    free_split(pos_split);
    free_split(orient_split);
    return 0;
}

int parse_light(char **split, t_data *data)
{
    if (data->light.brightness != -1)
        return (ft_printf("Error: Light already defined\n"), 1);
    if (!split[1] || !split[2] || !split[3])
        return (ft_printf("Error: Invalid light format\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **color_split = ft_split(split[3], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(pos_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid light position or color format\n"), 1);
    }

    data->light.pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    data->light.brightness = ft_atof(split[2]);
    data->light.color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(color_split);

    if (validate_color(data->light.color))
        return 1;

    return 0;
}

int parse_object(char **split, t_data *data, t_object_type type)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    if (type == SPHERE)
    {
        return parse_sphere(split, obj, data);
    }
    else if (type == PLANE)
    {
        return parse_plane(split, obj, data);
    }
    else if (type == CYLINDER)
    {
        return parse_cylinder(split, obj, data);
    }

    free(obj);
    return (ft_printf("Error: Unknown object type\n"), 1);
}

int parse_sphere(char **split, t_object *obj, t_data *data)
{
    if (!split[1] || !split[2] || !split[3])
        return (ft_printf("Error: Invalid sphere format\n"), free(obj), 1);

    char **pos_split = ft_split(split[1], ',');
    char **color_split = ft_split(split[3], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(pos_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid sphere position or color format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};
    obj->specific.sphere.diameter = ft_atof(split[2]);

    free_split(pos_split);
    free_split(color_split);

    if (validate_color(obj->color))
        return 1;

    obj->type = SPHERE;
    obj->is_selected = false;
    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

int parse_plane(char **split, t_object *obj, t_data *data)
{
    if (!split[1] || !split[2] || !split[3])
        return (ft_printf("Error: Invalid plane format\n"), free(obj), 1);

    char **pos_split = ft_split(split[1], ',');
    char **normal_split = ft_split(split[2], ',');
    char **color_split = ft_split(split[3], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !normal_split || !normal_split[0] || !normal_split[1] || !normal_split[2] || !color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(pos_split);
        free_split(normal_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid plane position, normal, or color format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->specific.plane.normal = (t_vector){ft_atof(normal_split[0]), ft_atof(normal_split[1]), ft_atof(normal_split[2])};
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(normal_split);
    free_split(color_split);

    if (validate_color(obj->color))
        return 1;

    obj->type = PLANE;
    obj->is_selected = false;
    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

int parse_cylinder(char **split, t_object *obj, t_data *data)
{
    if (!split[1] || !split[2] || !split[3] || !split[4] || !split[5])
        return (ft_printf("Error: Invalid cylinder format\n"), free(obj), 1);

    char **pos_split = ft_split(split[1], ',');
    char **axis_split = ft_split(split[2], ',');
    char **color_split = ft_split(split[5], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !axis_split || !axis_split[0] || !axis_split[1] || !axis_split[2] || !color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(pos_split);
        free_split(axis_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid cylinder position, axis, or color format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->specific.cylinder.axis = (t_vector){ft_atof(axis_split[0]), ft_atof(axis_split[1]), ft_atof(axis_split[2])};
    obj->specific.cylinder.diameter = ft_atof(split[3]);
    obj->specific.cylinder.height = ft_atof(split[4]);
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(axis_split);
    free_split(color_split);

    if (validate_color(obj->color))
        return 1;

    obj->type = CYLINDER;
    obj->is_selected = false;
    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

int parse_line(char *line, t_data *data)
{
    char **split = ft_split(line, ' ');
    if (!split)
        return (ft_printf("Error: Memory allocation failed\n"), 1);
    if (!split[0])
    {
        free_split(split);
        return 0;
    }

    if (ft_strcmp(split[0], "A") == 0)
    {
        if (parse_ambient(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "C") == 0)
    {
        if (parse_camera(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "L") == 0)
    {
        if (parse_light(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "sp") == 0)
    {
        if (parse_object(split, data, SPHERE))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "pl") == 0)
    {
        if (parse_object(split, data, PLANE))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "cy") == 0)
    {
        if (parse_object(split, data, CYLINDER))
        {
            free_split(split);
            return 1;
        }
    }
    else
    {
        ft_printf("Error: Unknown object type '%s'\n", split[0]);
        free_split(split);
        return 1;
    }

    free_split(split);
    return 0;
}

char *construct_scene_path(const char *filename)
{
    const char *scene_dir = "Scene/";
    size_t len = ft_strlen(scene_dir) + ft_strlen(filename) + 1;
    char *filepath = malloc(len);
    if (filepath)
    {
        ft_strlcpy(filepath, scene_dir, len);
        ft_strlcat(filepath, filename, len);
    }
    return filepath;
}
