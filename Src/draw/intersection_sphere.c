/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 23:51:04 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 00:08:29 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/miniRT.h"

/* Calcul le vecteur oc, la difference entre l'origine du rayon et le centre de
la sphere. */

static t_vector	*get_oc_vector(t_vector *ray_origin, t_vector *object_center)
{
	t_vector *vector_oc;

	vector_oc = (t_vector *)malloc(sizeof(t_vector));
	if (!vector_oc)
		return (NULL);
	vector_oc->x = ray_origin->x - object_center->x;
	vector_oc->y = ray_origin->y - object_center->y;
	vector_oc->z = ray_origin->z - object_center->z;
	return (vector_oc);
}

/* Calcul le produit scalaire de deux vecteurs. Ce dernier permet de determiner
les composantes suivantes des equations des coefficients :

- Pour 'A' : le produit scalaire de la direction du rayon, soit la longueur du
vecteur directionnel au carre.
- Pour 'B' : le produit scalaire entre le vecteur oc et la direction du rayon,
soit l'eloignement ou le rapprochement du rayon lancee de la zone d'intersection
de la sphere.
- Pour 'c' : le produit scalaire du vecteur oc sur lui-meme, soit la distance au
carre entre le centre de la sphere et l'origine du rayon. */

static double	get_scalar_product(t_vector *a, t_vector *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

/* Calcul le discriminant */

static double	get_delta(t_inter *inter)
{
	return (square(inter->coef_b) - 4 * inter->coef_a * inter->coef_c);
}

/* Determine si un rayon intersecte la sphere, et si oui, a quelle distance
cette inserction se produit le long du rayon. */

int	sphere_intersection(t_data *data, t_sphere *sphere, t_vector *ray_dir)
{
	t_vector	*oc;
	double		radius;
	double		delta;
	double		r1;
	double		r2;

	data->inter = malloc(sizeof(t_inter));
	oc = get_oc_vector(&data->camera.pos, &data->objects->pos);
	radius = sphere->diameter / 2;
	data->inter->coef_a = get_scalar_product(ray_dir, ray_dir);
	data->inter->coef_b = 2 * get_scalar_product(oc, ray_dir);
	data->inter->coef_c = get_scalar_product(oc, oc) - (radius * radius);
	delta = get_delta(data->inter);
	if (delta < 0)
		return (0);
	else
	{
		r1 = (-data->inter->coef_b - sqrt(delta)) / (2 * data->inter->coef_a);
		r2 = (-data->inter->coef_b + sqrt(delta)) / (2 * data->inter->coef_a);
		if (r1 > 0 || r2 > 0)
				return (1);
		return (0);
	}
}
