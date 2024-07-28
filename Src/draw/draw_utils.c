/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:47:34 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/28 23:48:49 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

double	square(double x)
{
	return (x * x);
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
