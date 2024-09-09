#include "miniRT.h"

int main(int argc, char **argv)
{
    t_data *data = malloc(sizeof(t_data));
    if (!data)
    {
        ft_printf("Error: Memory allocation failed\n");
        return (1);
    }
	ft_memset(data, 0, sizeof(t_data));

    if (argc != 2)
    {
        ft_printf("Usage: %s <scene.rt>\n", argv[0]);
        free(data);
        return (1);
    }

    // Initialize MiniLibX
    data->mlx = mlx_init();
    if (data->mlx == NULL)
    {
        free(data);
        return (1);
    }
    data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
    if (data->window == NULL)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        free(data);
        return (1);
    }

    // Initialize scene data
    data->objects = NULL;
    data->object_count = 0;

    // Parse the scene file
    if (validate_filename(argv[1]) != 0)
    {
        ft_printf("Error: Invalid file extension. Expected .rt file.\n");
        free_data(data);
        return (1);
    }

    if (parse_scene(argv[1], data) != 0)
    {
        ft_printf("Error parsing scene\n");
        free_data(data);
        return (1);
    }

    if (validate_scene_elements(data) != 0)
    {
        ft_printf("Error: Invalid scene elements\n");
        free_data(data);
        return (1);
    }

    // Render
    init_mlx_image(data);
    raytracing(data);
    mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);

    // Events and loop
    mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 17, 0, handle_close, data);
    mlx_loop(data->mlx);

    // Free resources
    free_data(data);
    return (0);
}
