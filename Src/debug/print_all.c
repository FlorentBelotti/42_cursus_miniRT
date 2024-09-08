#include "miniRT.h"
#include <stdio.h>

void debug_print_vector(const t_vector *vec)
{
    printf("Vector(x: %.2f, y: %.2f, z: %.2f)\n", vec->x, vec->y, vec->z);
}

void debug_print_color(const t_color *color)
{
    printf("Color(r: %d, g: %d, b: %d)\n", color->r, color->g, color->b);
}

void debug_print_noise(const t_noise *noise)
{
    if (noise->octaves > 0)
    {
        printf("Perlin Noise:\n");
        printf("  Octaves: %d\n", noise->octaves);
        printf("  Persistence: %.2f\n", noise->persistence);
        printf("  Frequency: %.2f\n", noise->frequency);
        printf("  Intensity: %.2f\n", noise->intensity);
    }
}

void debug_print_object(const t_object *obj)
{
    printf("\nObject Type: ");
    if (obj->type == SPHERE)
    {
        printf("Sphere\n");
        printf("Position: ");
        debug_print_vector(&obj->pos);
        printf("Color: ");
        debug_print_color(&obj->color);
        printf("Diameter: %.2f\n", obj->specific.sphere.diameter);
    }
    else if (obj->type == PLANE)
    {
        printf("Plane\n");
        printf("Position: ");
        debug_print_vector(&obj->pos);
        printf("Color: ");
        debug_print_color(&obj->color);
        printf("Normal: ");
        debug_print_vector(&obj->specific.plane.normal);
    }
    else if (obj->type == CYLINDER)
    {
        printf("Cylinder\n");
        printf("Position: ");
        debug_print_vector(&obj->pos);
        printf("Color: ");
        debug_print_color(&obj->color);
        printf("Axis: ");
        debug_print_vector(&obj->specific.cylinder.axis);
        printf("Diameter: %.2f\n", obj->specific.cylinder.diameter);
        printf("Height: %.2f\n", obj->specific.cylinder.height);
    }
    else if (obj->type == CONE)
    {
        printf("Cone\n");
        printf("Position: ");
        debug_print_vector(&obj->pos);
        printf("Color: ");
        debug_print_color(&obj->color);
		printf("Axis: ");
        debug_print_vector(&obj->specific.cone.axis);
        printf("Diameter: %.2f\n", obj->specific.cone.diameter);
        printf("Height: %.2f\n", obj->specific.cone.height);
    }

    // Print checkerboard info
    printf("Checkerboard: %s\n", obj->checkerboard ? "Yes" : "No");

    // Print Perlin noise info (if applicable)
    if (obj->noise.octaves > 0)
    {
        printf("Perlin Noise:\n");
        printf("  Octaves: %d\n", obj->noise.octaves);
        printf("  Persistence: %.2f\n", obj->noise.frequency);
        printf("  Frequency: %.2f\n", obj->noise.persistence);
        printf("  Intensity: %.2f\n", obj->noise.intensity);
    }
    else
    {
        printf("Perlin Noise: None\n");
    }

    printf("Is Selected: %s\n", obj->is_selected ? "True" : "False");
}

void debug_print_scene(t_data *data)
{
    printf("Ambient Light:\n");
    printf("Ratio: %.2f\n", data->ambient.ratio);
    printf("Color: ");
    debug_print_color(&data->ambient.color);

    printf("\nCamera:\n");
    printf("Position: ");
    debug_print_vector(&data->camera.pos);
    printf("Orientation: ");
    debug_print_vector(&data->camera.orient);
    printf("FOV: %d\n", data->camera.fov);

    printf("\nLights:\n");
    t_light *current_light = data->light;
    while (current_light)
    {
        printf("Position: ");
        debug_print_vector(&current_light->pos);
        printf("Brightness: %.2f\n", current_light->brightness);
        printf("Color: ");
        debug_print_color(&current_light->color);
        current_light = current_light->next;
    }

    printf("\nObjects (%d):\n", data->object_count);
    t_object *current = data->objects;
    while (current)
    {
        debug_print_object(current);
        current = current->next;
    }
}
