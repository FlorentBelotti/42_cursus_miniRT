#include "miniRT.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        ft_printf("Usage: %s <scene.rt>\n", argv[0]);
        return (1);
    }

    // Initialiser MiniLibX
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

    // Initialiser les données de scène
    data.objects = NULL;
    data.object_count = 0;

    // Parser le fichier de scène
    if (parse_scene(argv[1], &data) != 0)
    {
        ft_printf("Error parsing scene\n");
        return (1);
    }

	//TO DELETE (DEBUG)
	debug_print_scene(&data);

    // Ajouter les gestionnaires d'événements
    // mlx_key_hook(data.window, handle_keypress, &data);
    // mlx_mouse_hook(data.window, handle_mouse, &data);

    // Boucle principale
    mlx_loop(data.mlx);

    // Libérer les ressources
    free_objects(data.objects);
    return (0);
}
