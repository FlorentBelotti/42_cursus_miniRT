/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:49:05 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 03:00:41 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

void ft_mlx_pixel_put(t_img *img, int x, int y)
{
	char *dst;
	unsigned int red = 0xFFFF0000; // ARGB pour le rouge plein
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return;
	dst = img->img_addr + (y * img->line_len + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = red;
}

void init_mlx_image(t_data *data)
{
	data->img = malloc(sizeof(t_img));
	if (!data->img)
		return;
	data->img->img_ptr = mlx_new_image(data->mlx,
									   WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->img->img_ptr)
	{
		free(data->img);
		return;
	}
	data->img->img_addr = mlx_get_data_addr(data->img->img_ptr,
			&(data)->img->bits_per_pixel, &(data)->img->line_len,
					&(data)->img->endian);
}
