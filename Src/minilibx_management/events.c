/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 17:33:38 by fbelotti          #+#    #+#             */
/*   Updated: 2024/09/09 17:31:47 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

static int	close_minirt(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

static void	ft_mlx_clear_window(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			ft_mlx_pixel_put(data->img, i, j, 0);
			i++;
		}
		j++;
	}
}

void	update_draw(t_data *data)
{
	ft_mlx_clear_window(data);
	raytracing(data);
	mlx_put_image_to_window(data->mlx, data->window, data->img->img_ptr, 0, 0);
}

int	handle_keypress(int key_code, t_data *data)
{
	if (key_code == KEY_ESC)
		close_minirt(data);
	else if (key_code >= KEY_A && key_code <= KEY_W)
		apply_movement_to_camera(key_code, data);
	else if (key_code >= KEY_LEFT && key_code <= KEY_DOWN)
		apply_rotation_to_camera(key_code, data);
	return (0);
}

int	handle_close(t_data *data)
{
	close_minirt(data);
	return (0);
}
