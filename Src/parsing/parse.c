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
    if (data->light->brightness == -1)
    {
        ft_printf("Error: Light not defined\n");
        return 1;
    }
    return 0;
}

// Parse ambient light
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

    return 0;
}

// Parse camera
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

// Parse light
int parse_light(char **split, t_data *data)
{
    t_light *new_light = malloc(sizeof(t_light));
    if (!new_light)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    if (!split[1] || !split[2] || !split[3])
        return (ft_printf("Error: Invalid light format\n"), free(new_light), 1);

    char **pos_split = ft_split(split[1], ',');
    char **color_split = ft_split(split[3], ',');
    if (!pos_split || !pos_split[0] || !pos_split[1] || !pos_split[2] || !color_split || !color_split[0] || !color_split[1] || !color_split[2])
    {
        free_split(pos_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid light position or color format\n"), free(new_light), 1);
    }

    new_light->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    new_light->brightness = ft_atof(split[2]);
    new_light->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};
    new_light->next = NULL;

    free_split(pos_split);
    free_split(color_split);

    // Add the new light to the list
    if (data->light == NULL)
        data->light = new_light;
    else
    {
        t_light *current = data->light;
        while (current->next)
            current = current->next;
        current->next = new_light;
    }

    return 0;
}


#include "miniRT.h"

// Helper function to construct file path for the scene
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

// General scene parsing
int parse_scene(const char *filename, t_data *data)
{
    char *filepath = construct_scene_path(filename);
    int fd = open(filepath, O_RDONLY);
    free(filepath);
    if (fd < 0)
        return (ft_printf("Error: Unable to open file %s\n", filename), 1);

    char *line;
    data->ambient.ratio = -1;
    data->camera.fov = -1;
    data->light = NULL;

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

    if (data->ambient.ratio == -1 || data->camera.fov == -1 || data->light == NULL || data->light->brightness == -1)
        return (ft_printf("Error: Missing mandatory scene elements\n"), 1);

    return 0;
}

// Parse individual line in the scene file
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
        if (parse_sphere(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "pl") == 0)
    {
        if (parse_plane(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "cy") == 0)
    {
        if (parse_cylinder(split, data))
        {
            free_split(split);
            return 1;
        }
    }
    else if (ft_strcmp(split[0], "par") == 0)
    {
        if (parse_paraboloid(split, data))
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

int parse_object_options(char **split, t_object *obj)
{
    for (int i = 4; split[i] != NULL; i++)
    {
        if (ft_strcmp(split[i], "checkerboard") == 0 || ft_strcmp(split[i], "checkerboard\n") == 0)
        {
            obj->checkerboard = true;  // Set checkerboard flag
        }
        else if (ft_strcmp(split[i], "P") == 0)  // Handle Perlin noise
        {
            // Ensure enough parameters follow "P"
            if (!split[i + 1] || !split[i + 2] || !split[i + 3] || !split[i + 4])
                return (ft_printf("Error: Invalid Perlin noise format\n"), 1);

            // Set Perlin noise parameters
            obj->noise.octaves = ft_atoi(split[i + 1]);
            obj->noise.frequency = ft_atof(split[i + 2]);
            obj->noise.persistence = ft_atof(split[i + 3]);
            obj->noise.intensity = ft_atof(split[i + 4]);

            // Skip past Perlin noise parameters
            i += 4;
        }
    }

    return 0;
}

// Parse Perlin noise settings
int parse_perlin_noise(char **split, t_noise *noise)
{
    if (!split[1] || !split[2] || !split[3] || !split[4])
        return (ft_printf("Error: Invalid Perlin noise format\n"), 1);

    noise->octaves = ft_atoi(split[1]);
    noise->frequency = ft_atof(split[2]);
    noise->persistence = ft_atof(split[3]);
    noise->intensity = ft_atof(split[4]);

    return 0;
}

// Parse sphere
int parse_sphere(char **split, t_data *data)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **color_split = ft_split(split[3], ',');

    if (!pos_split || !color_split)
    {
        free_split(pos_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid sphere format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};
    obj->specific.sphere.diameter = ft_atof(split[2]);

    free_split(pos_split);
    free_split(color_split);

    obj->type = SPHERE;

    if (parse_object_options(split, obj))
        return 1;

    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

// Parse plane
int parse_plane(char **split, t_data *data)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **normal_split = ft_split(split[2], ',');
    char **color_split = ft_split(split[3], ',');

    if (!pos_split || !normal_split || !color_split)
    {
        free_split(pos_split);
        free_split(normal_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid plane format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->specific.plane.normal = (t_vector){ft_atof(normal_split[0]), ft_atof(normal_split[1]), ft_atof(normal_split[2])};
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(normal_split);
    free_split(color_split);

    obj->type = PLANE;
    obj->checkerboard = false;  // Initialize to false
    memset(&obj->noise, 0, sizeof(t_noise));  // Initialize noise to zero

    if (parse_object_options(split, obj))
    {
        free(obj);
        return 1;
    }

    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

// Parse cylinder
int parse_cylinder(char **split, t_data *data)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **axis_split = ft_split(split[2], ',');
    char **color_split = ft_split(split[5], ',');

    if (!pos_split || !axis_split || !color_split)
    {
        free_split(pos_split);
        free_split(axis_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid cylinder format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->specific.cylinder.axis = (t_vector){ft_atof(axis_split[0]), ft_atof(axis_split[1]), ft_atof(axis_split[2])};
    obj->specific.cylinder.diameter = ft_atof(split[3]);
    obj->specific.cylinder.height = ft_atof(split[4]);
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(axis_split);
    free_split(color_split);

    obj->type = CYLINDER;

    if (parse_object_options(split, obj))
        return 1;

    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}

// Parse paraboloid
int parse_paraboloid(char **split, t_data *data)
{
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (ft_printf("Error: Memory allocation failed\n"), 1);

    char **pos_split = ft_split(split[1], ',');
    char **orient_split = ft_split(split[4], ',');
    char **color_split = ft_split(split[5], ',');

    if (!pos_split || !orient_split || !color_split)
    {
        free_split(pos_split);
        free_split(orient_split);
        free_split(color_split);
        return (ft_printf("Error: Invalid paraboloid format\n"), free(obj), 1);
    }

    obj->pos = (t_vector){ft_atof(pos_split[0]), ft_atof(pos_split[1]), ft_atof(pos_split[2])};
    obj->specific.paraboloid.demi_axe_a = ft_atof(split[2]);
    obj->specific.paraboloid.demi_axe_b = ft_atof(split[3]);
    obj->specific.paraboloid.height = ft_atof(split[4]);
    obj->specific.paraboloid.orient = (t_vector){ft_atof(orient_split[0]), ft_atof(orient_split[1]), ft_atof(orient_split[2])};
    obj->color = (t_color){ft_atoi(color_split[0]), ft_atoi(color_split[1]), ft_atoi(color_split[2])};

    free_split(pos_split);
    free_split(orient_split);
    free_split(color_split);

    obj->type = PARABOLOID;

    if (parse_object_options(split, obj))
        return 1;

    obj->next = data->objects;
    data->objects = obj;
    data->object_count++;
    return 0;
}
