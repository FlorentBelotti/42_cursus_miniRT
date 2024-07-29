/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:49:32 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/29 02:59:43 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include "42_cursus_libft/Includes/libft.h"

// Dimensions de la fenêtre
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

// Identifiants des objets
typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER
} t_object_type;

// Structures de base
typedef struct s_vector
{
	double x;
	double y;
	double z;
} t_vector;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

// Sous-structures pour les objets
typedef struct s_sphere
{
	double diameter;
} t_sphere;

typedef struct s_plane
{
	t_vector normal;
} t_plane;

typedef struct s_cylinder
{
	double diameter;
	double height;
	t_vector axis;
} t_cylinder;

// Structure principale de l'objet
typedef struct s_object
{
	t_object_type type;
	bool is_selected;
	t_vector pos;
	t_color color;
	union
	{
		t_sphere sphere;
		t_plane plane;
		t_cylinder cylinder;
	} specific;
	struct s_object *next;
} t_object;

// Structure de la scène
typedef struct s_ambient
{
	double ratio;
	t_color color;
} t_ambient;

typedef struct s_camera
{
	t_vector pos;
	t_vector orient;
	int fov;
} t_camera;

typedef struct s_light
{
	t_vector pos;
	double brightness;
	t_color color;
} t_light;

typedef struct s_keys
{
	int w;
	int a;
	int s;
	int d;
	int q;
	int e;
	int t;
	int y;
	int g;
	int h;
	int b;
	int n;
} t_keys;

typedef struct s_ray
{
	t_vector direction;
} t_ray;

typedef struct s_inter
{
	double		coef_a;
	double		coef_b;
	double		coef_c;
	double		radius;
	double		delta;
	double		r1;
	double		r2;
	t_vector	*oc;
} t_inter;

typedef struct s_img
{
	void			*img_ptr;
	char			*img_addr;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}	t_img;

typedef struct s_data
{
	void *mlx;
	void *window;
	int object_count;
	int farthest_object;
	double total_rays;
	t_ambient ambient;
	t_camera camera;
	t_light light;
	t_object *objects;
	t_keys keys;
	t_ray	*rays;
	t_inter	*inter;
	t_img	*img;
} t_data;

// Prototypes de fonctions
int		parse_scene(const char *filename, t_data *data);
int		parse_ambient(char **split, t_data *data);
int		parse_camera(char **split, t_data *data);
int		parse_light(char **split, t_data *data);
int		parse_object(char **split, t_data *data, t_object_type type);
int		parse_sphere(char **split, t_object *obj, t_data *data);
int		parse_plane(char **split, t_object *obj, t_data *data);
int		parse_cylinder(char **split, t_object *obj, t_data *data);
int		parse_line(char *line, t_data *data);
char	*construct_scene_path(const char *filename);

void	free_objects(t_object *objects);
void	free_split(char **split);
double	ft_atof(const char *str);

// Validation functions
int		validate_filename(const char *filename);
int		validate_scene_elements(t_data *data);

// Event handling functions
int		handle_keypress(int keycode, t_data *data);
int		handle_keyrelease(int keycode, t_data *data);
int		handle_mouse(int button, int x, int y, t_data *data);
void	update_object_position(t_object *obj, t_keys *keys);
int		loop_hook(t_data *data);
void	reset_keys(t_keys *keys);

// Fonction de débogage
void	debug_print_scene(t_data *data);
void	print_rays(t_data *data);

//Raytracing
int		raytracing(t_data *data);

//Intersection calculation
int		sphere_intersection(t_data *data, t_sphere *sphere, t_vector *ray_dir);
int	cylinder_intersection(t_data *data, t_cylinder *cylinder, t_vector *ray_dir);
int plane_intersection(t_data *data, t_plane *plane, t_vector *ray_dir);

//Render
void	render(t_data *data);

//Minilibx
void	init_mlx_image(t_data *data);
void	ft_mlx_pixel_put(t_img *img, int x, int y);

//draw_utils
double		square(double x);
t_vector	*get_oc_vector(t_vector *ray_origin, t_vector *object_center);
double		get_scalar_product(t_vector *a, t_vector *b);
double		get_delta(t_inter *inter);

#endif
