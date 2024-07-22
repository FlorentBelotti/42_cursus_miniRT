/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:49:32 by fbelotti          #+#    #+#             */
/*   Updated: 2024/07/22 19:56:21 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "minilibx-linux/mlx.h"
# include "42_cursus_libft/Includes/libft.h"
# include <string.h>

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

typedef struct s_data
{
    void *mlx;
    void *window;
    t_ambient ambient;
    t_camera camera;
    t_light light;
    t_object *objects;
    int object_count;
    t_keys keys;
} t_data;

// Prototypes de fonctions
int parse_scene(const char *filename, t_data *data);
int parse_ambient(char **split, t_data *data);
int parse_camera(char **split, t_data *data);
int parse_light(char **split, t_data *data);
int parse_object(char **split, t_data *data, t_object_type type);
int parse_sphere(char **split, t_object *obj, t_data *data);
int parse_plane(char **split, t_object *obj, t_data *data);
int parse_cylinder(char **split, t_object *obj, t_data *data);
int parse_line(char *line, t_data *data);
char *construct_scene_path(const char *filename);

void free_objects(t_object *objects);
void free_split(char **split);
double ft_atof(const char *str);

// Validation functions
int validate_filename(const char *filename);
int validate_scene_elements(t_data *data);

// Event handling functions
int handle_keypress(int keycode, t_data *data);
int handle_keyrelease(int keycode, t_data *data);
int handle_mouse(int button, int x, int y, t_data *data);
void update_object_position(t_object *obj, t_keys *keys);
int loop_hook(t_data *data);
void reset_keys(t_keys *keys);

// Fonction de débogage
void debug_print_scene(t_data *data);

#endif
