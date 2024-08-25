/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbelotti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:49:32 by fbelotti          #+#    #+#             */
/*   Updated: 2024/08/26 01:31:31 by fbelotti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <math.h>
# include <float.h>
# include "minilibx-linux/mlx.h"
# include "42_cursus_libft/Includes/libft.h"

// Dimensions de la fenêtre
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define EPSILON 1e-6

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
	t_vector right;
	t_vector up;
	int fov;
	double fov_rad;
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
	t_vector origin;
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
	double		ray_dir_v;
	double		cylinder_min;
	double		cylinder_max;
	double		P1_proj;
	double		P2_proj;
	double		oc_v;
	t_vector	oc;
	t_vector	oc_perp;
	t_vector	dir_perp;
	t_vector	cylinder_center;
	t_vector	P1;
	t_vector	P2;
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
	double view_width;
	double view_height;
	double z_buffer[WINDOW_HEIGHT][WINDOW_WIDTH];
	t_ambient ambient;
	t_camera camera;
	t_light light;
	t_object *objects;
	t_keys keys;
	t_ray	ray;
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
void	debug_print_object(const t_object *obj);
void	print_rays(t_data *data);

//render
void	render(t_data *data, t_ray *ray, int x, int y);
double		get_low_intersection_distance(t_object *object, t_ray *ray);
double	get_high_intersection_distance(t_object *object, t_ray *ray);

//lightning
t_color	get_pixel_lighting(t_data *data, t_object *object, t_vector intersection);
t_color	get_ambient_light(t_ambient ambient, t_color object_color);
int		get_shadow_factor(t_data *data, t_vector intersection, t_light light);
double	get_light_distance(t_vector a, t_vector b);

//Raytracing
int		raytracing(t_data *data);

//Intersection calculation
double	sphere_intersection(t_sphere *sphere, t_ray *ray, t_object *current);
double	cylinder_intersection(t_cylinder *cylinder, t_ray *ray, t_object *current);
double	plane_intersection(t_plane *plane, t_ray *ray, t_vector *pos);

//Minilibx
void	init_mlx_image(t_data *data);
int		rgb_to_int(t_color color);
void	ft_mlx_pixel_put(t_img *img, int x, int y, int color);

//vector_utils
t_vector	vector_cross(t_vector a, t_vector b);
t_vector	get_oc_vector(t_vector *ray_origin, t_vector *object_center);
t_vector	mul(t_vector a, double b);
t_vector	sub(t_vector a, t_vector b);
t_vector	add(t_vector a, t_vector b);
void		normalize_vector(t_vector *v);
double		square(double x);
double		get_scalar_product(const t_vector *a, const t_vector *b);
double		get_delta(t_inter *inter);

#endif
