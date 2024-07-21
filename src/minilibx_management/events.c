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

int handle_keypress(int keycode, t_data *data)
{
    t_object *obj = data->objects;

    while (obj)
    {
        if (obj->is_selected)
        {
            if (keycode == KEY_W)
                obj->pos.z += 1.0;
            else if (keycode == KEY_S)
                obj->pos.z -= 1.0;
            else if (keycode == KEY_A)
                obj->pos.x -= 1.0;
            else if (keycode == KEY_D)
                obj->pos.x += 1.0;
            else if (keycode == KEY_Q)
                obj->pos.y += 1.0;
            else if (keycode == KEY_E)
                obj->pos.y -= 1.0;
            // Add rotation logic for T, Y, G, H, B, N keys
            else if (keycode == KEY_T)
                ; // Rotate object around X axis clockwise
            else if (keycode == KEY_Y)
                ; // Rotate object around X axis counterclockwise
            else if (keycode == KEY_G)
                ; // Rotate object around Y axis clockwise
            else if (keycode == KEY_H)
                ; // Rotate object around Y axis counterclockwise
            else if (keycode == KEY_B)
                ; // Rotate object around Z axis clockwise
            else if (keycode == KEY_N)
                ; // Rotate object around Z axis counterclockwise
        }
        obj = obj->next;
    }
    return 0;
}

int handle_mouse(int button, int x, int y, t_data *data)
{
    if (button == 1) // Left click
    {
        // Logic to detect object selection based on x, y coordinates
        // If object is selected, set obj->is_selected to true
    }
    return 0;
}
