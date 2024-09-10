/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 17:41:44 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/09 17:41:45 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	initialize_and_check(t_data **data, int argc, char **argv)
{
	t_data	*temp;

	temp = malloc(sizeof(t_data));
	if (!temp)
	{
		ft_printf("Error: Memory allocation failed\n");
		return (1);
	}
	ft_memset(temp, 0, sizeof(t_data));
	*data = temp;
	if (argc != 2)
	{
		ft_printf("Usage: %s <scene.rt>\n", argv[0]);
		free(temp);
		return (1);
	}
	return (0);
}

static int	setup_mlx_environment(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		return (1);
	}
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"MiniRT");
	if (data->window == NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (1);
	}
	return (0);
}

static int	parse_and_validate_scene(char *filename, t_data *data)
{
	if (validate_filename(filename) != 0)
	{
		ft_printf("Error: Invalid file extension. Expected .rt file.\n");
		return (1);
	}
	if (parse_scene(filename, data) != 0)
	{
		ft_printf("Error parsing scene\n");
		return (1);
	}
	if (validate_scene_elements(data) != 0)
	{
		ft_printf("Error: Invalid scene elements\n");
		return (1);
	}
	return (0);
}

static void	render_and_setup_hooks(t_data *data)
{
	init_mlx_image(data);
	raytracing(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
	mlx_key_hook(data->window, handle_keypress, data);
	mlx_hook(data->window, 17, 0, handle_close, data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (initialize_and_check(&data, argc, argv) != 0)
		return (1);
	if (setup_mlx_environment(data) != 0)
	{
		free(data);
		return (1);
	}
	data->objects = NULL;
	data->object_count = 0;
	if (parse_and_validate_scene(argv[1], data) != 0)
	{
		free_data(data);
		return (1);
	}
	render_and_setup_hooks(data);
	mlx_loop(data->mlx);
	free_data(data);
	return (0);
}
