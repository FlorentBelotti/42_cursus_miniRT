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

    printf("\nLight:\n");
    printf("Position: ");
    debug_print_vector(&data->light.pos);
    printf("Brightness: %.2f\n", data->light.brightness);
    printf("Color: ");
    debug_print_color(&data->light.color);

    printf("\nObjects (%d):\n", data->object_count);
    t_object *current = data->objects;
    while (current)
    {
        debug_print_object(current);
        current = current->next;
    }
}

void print_rays(t_data *data)
{
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) { // Limite à 2 rayons par ligne
            int i = y * WINDOW_WIDTH + x;
            t_ray ray = data->rays[i];
            printf("Ray [%d, %d] -> Direction: (x: %.2f, y: %.2f, z: %.2f)\n",
                   x, y, ray.direction.x, ray.direction.y, ray.direction.z);
        }
    }
}
