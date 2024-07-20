#include "miniRT.h"

int	main(void)
{
	void	*mlx;
	void	*window;

	mlx = mlx_init();
	if (mlx == NULL)
		return (1);
	window = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT");
	if (window == NULL)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	mlx_loop(mlx);
	return (0);
}
