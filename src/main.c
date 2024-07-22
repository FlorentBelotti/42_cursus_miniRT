#include "miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        ft_printf("Usage: %s <scene.rt>\n", argv[0]);
        return (1);
    }

    // Initialize MiniLibX
    data.mlx = mlx_init();
    if (data.mlx == NULL)
        return (1);
    data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
    if (data.window == NULL)
    {
        mlx_destroy_display(data.mlx);
        free(data.mlx);
        return (1);
    }

    // Initialize scene data
    data.objects = NULL;
    data.object_count = 0;
    reset_keys(&data.keys);

    // Parse the scene file
    if (validate_filename(argv[1]) != 0)
    {
        ft_printf("Error: Invalid file extension. Expected .rt file.\n");
        return (1);
    }

    if (parse_scene(argv[1], &data) != 0)
    {
        ft_printf("Error parsing scene\n");
		//add free
        return (1);
    }

    if (validate_scene_elements(&data) != 0)
    {
        ft_printf("Error: Invalid scene elements\n");
		//add free
        return (1);
    }

	//DELETE THE DEBUG
	debug_print_scene(&data);

    // Add event handlers
    mlx_hook(data.window, 2, 1L<<0, handle_keypress, &data);
    mlx_hook(data.window, 3, 1L<<1, handle_keyrelease, &data);
    // mlx_mouse_hook(data.window, handle_mouse, &data); // Handle mouse events (left click to select)

    mlx_loop_hook(data.mlx, loop_hook, &data);

    // Main loop
    mlx_loop(data.mlx);

    // Free resources
    free_objects(data.objects);
    return (0);
}
