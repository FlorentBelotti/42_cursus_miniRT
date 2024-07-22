#include "miniRT.h"

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_Q 12
#define KEY_E 14
#define KEY_T 17
#define KEY_Y 16
#define KEY_G 5
#define KEY_H 4
#define KEY_B 11
#define KEY_N 45
#define KEY_ESC 53

void reset_keys(t_keys *keys)
{
    keys->w = 0;
    keys->a = 0;
    keys->s = 0;
    keys->d = 0;
    keys->q = 0;
    keys->e = 0;
    keys->t = 0;
    keys->y = 0;
    keys->g = 0;
    keys->h = 0;
    keys->b = 0;
    keys->n = 0;
}

int handle_keypress(int keycode, t_data *data)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(data->mlx, data->window);
        exit(0);
    }
    else if (keycode == KEY_W)
        data->keys.w = 1;
    else if (keycode == KEY_A)
        data->keys.a = 1;
    else if (keycode == KEY_S)
        data->keys.s = 1;
    else if (keycode == KEY_D)
        data->keys.d = 1;
    else if (keycode == KEY_Q)
        data->keys.q = 1;
    else if (keycode == KEY_E)
        data->keys.e = 1;
    else if (keycode == KEY_T)
        data->keys.t = 1;
    else if (keycode == KEY_Y)
        data->keys.y = 1;
    else if (keycode == KEY_G)
        data->keys.g = 1;
    else if (keycode == KEY_H)
        data->keys.h = 1;
    else if (keycode == KEY_B)
        data->keys.b = 1;
    else if (keycode == KEY_N)
        data->keys.n = 1;
    return 0;
}

int handle_keyrelease(int keycode, t_data *data)
{
    if (keycode == KEY_W)
        data->keys.w = 0;
    else if (keycode == KEY_A)
        data->keys.a = 0;
    else if (keycode == KEY_S)
        data->keys.s = 0;
    else if (keycode == KEY_D)
        data->keys.d = 0;
    else if (keycode == KEY_Q)
        data->keys.q = 0;
    else if (keycode == KEY_E)
        data->keys.e = 0;
    else if (keycode == KEY_T)
        data->keys.t = 0;
    else if (keycode == KEY_Y)
        data->keys.y = 0;
    else if (keycode == KEY_G)
        data->keys.g = 0;
    else if (keycode == KEY_H)
        data->keys.h = 0;
    else if (keycode == KEY_B)
        data->keys.b = 0;
    else if (keycode == KEY_N)
        data->keys.n = 0;
    return 0;
}

void update_object_position(t_object *obj, t_keys *keys)
{
    if (keys->w)
        obj->pos.z += 1.0;
    if (keys->s)
        obj->pos.z -= 1.0;
    if (keys->a)
        obj->pos.x -= 1.0;
    if (keys->d)
        obj->pos.x += 1.0;
    if (keys->q)
        obj->pos.y += 1.0;
    if (keys->e)
        obj->pos.y -= 1.0;
    // Add rotation logic for T, Y, G, H, B, N keys
    // if (keys->t)
    //     ; // Rotate object around X axis clockwise
    // if (keys->y)
    //     ; // Rotate object around X axis counterclockwise
    // if (keys->g)
    //     ; // Rotate object around Y axis clockwise
    // if (keys->h)
    //     ; // Rotate object around Y axis counterclockwise
    // if (keys->b)
    //     ; // Rotate object around Z axis clockwise
    // if (keys->n)
    //     ; // Rotate object around Z axis counterclockwise
}

int loop_hook(t_data *data)
{
    t_object *obj = data->objects;
    while (obj)
    {
        if (obj->is_selected)
        {
            update_object_position(obj, &data->keys);
        }
        obj = obj->next;
    }
    return 0;
}

// int handle_mouse(int button, int x, int y, t_data *data)
// {
//     if (button == 1) // Left click
//     {
//         // Logic to detect object selection based on x, y coordinates
//         // If object is selected, set obj->is_selected to true
//     }
//     return 0;
// }
