<div align="left">

### 42_cursus_miniRT![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<div align="left">
    
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

<nav>
    
### Sommaire![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<ul>
    <li><a href="#Introduction">Introduction</a></li>
    <li><a href="#Render">Render</a></li>
    <li><a href="#Structure">Structure</a></li>
    <li><a href="#Code overview">Code overview</a></li>
    <li><a href="#Raytracing">Raytracing</a></li>
    <li><a href="#Lighting">Lighting</a></li>
    <li><a href="#Perlin algorithm">Perlin algorithm</a></li>
    <li><a href="#Checkerboard algorithm">Execution Breakdown</a></li>
    <li><a href="#Conclusion">Conclusion</a></li>
    <li><a href="#Thanks">Thanks</a></li>
</ul>
</nav>

### Introduction![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Introduction">

<div align="justify">

Le quatrième cercle des projets de l'école 42 propose aux étudiants deux choix dans le domaine du graphisme : Cub3d, un jeu en 3D minimaliste basé sur le raycasting, et MiniRT, qui consiste à développer un moteur de raytracing capable de générer des images en suivant les principes de l'optique géométrique. Cub3d, avec son approche axée sur la création d'un environnement interactif en 2.5D, est souvent privilégié pour son caractère ludique. MiniRT, en revanche, est perçu comme un projet plus technique, impliquant une compréhension fine des algorithmes et des mathématiques appliquées à la génération d'images de synthèse. C’est cette dimension algorithmique et mathématique qui a suscité mon intérêt, malgré mon parcours initialement littéraire. Je souhaitais m’attaquer à un projet qui m'obligerait à approfondir ces compétences, tout en relevant un défi personnel.

Pour organiser efficacement le travail, nous avons réparti les responsabilités avec mon partenaire. Il s'est chargé de la gestion du parsing des fichiers de scène et de l'intégration de la bibliothèque graphique, tandis que j’ai pris en main la mise en œuvre du raytracing et des algorithmes associés.

À mes yeux, MiniRT repose sur deux piliers essentiels : d’une part, l’implémentation d’algorithmes complexes en langage C, comme l’algorithme de Perlin pour le bruit procédural ; d’autre part, l’apprentissage progressif des étapes constitutives du raytracing, depuis l’intersection des rayons avec les objets jusqu'à la gestion des réflexions et ombres. Ce README a pour but de retracer ces différentes étapes, en mettant l'accent sur les difficultés rencontrées et les solutions apportées.

<div align="left">

### Render![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Render">

<div align="justify">

Pour commencer, voici quelques exemples du rendu final de mon miniRT.

<div align="left">

### Structure![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Structure">
    
```css
MiniRT/
├── include/
│   ├── Minilibx/
│   ├── Libft/
│   ├── miniRT.h
│
├── Scene/
│
├── Src/
│   ├── draw/
│   │   ├── checkerboard/
│   │   │   ├── checkerboard_algo.c/
│   │   │   ├── checkerboard.c/
│   │   │ 
│   │   ├── intersection/
│   │   │   ├── cap.c/
│   │   │   ├── cone.c/
│   │   │   ├── cylinder.c/
│   │   │   ├── intersection.c/
│   │   │   ├── plane.c/
│   │   │   ├── sphere.c/
│   │   │ 
│   │   ├── lighting/
│   │   │   ├── lighting.c/
│   │   │   ├── shadow.c/
│   │   │ 
│   │   ├── perlin/
│   │   │   ├── noise.c/
│   │   │   ├── perlin.c/
│   │   │ 
│   │   ├── utils/
│   │   │   ├── intersection_utils.c/
│   │   │   ├── lighting_utils.c/
│   │   │   ├── math_utils.c/
│   │   │   ├── noise_utils.c/
│   │   │   ├── vector_utils.c/
│   │   │ 
│   │   ├── raytracing.c
│   │   ├── render.c
│   │
│   ├── minilibx_management/
│   │   ├── camera_events.c
│   │   ├── events.c
│   │   ├── image.c
│   │
│   ├── parsing/
│   │   ├── free.c
│   │   ├── parse_camera_ambiant.c
│   │   ├── parse_cone_cy.c
│   │   ├── parse_file.c
│   │   ├── parse_light.c
│   │   ├── parse_scene.c
│   │   ├── parse_sp_pl.c
│   │   ├── parse_utils.c
│   │   ├── validate_utils.c
│   │
│   ├── main.c
│
├── Makefile
├── README.md
```


### Code overview![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Code overview">



### Raytracing![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Raytracing">

```css
void	render(t_data *data, t_ray *ray, int x, int y)
{
	t_object	*current_object;
	t_object	*closest_object;
	t_vector	intersection;
	t_color		color;
	double		d;

	current_object = data->objects;
	closest_object = NULL;
	while (current_object)
	{
		d = get_intersection_distance(current_object, ray, -1);
		if (d >= EPSILON && d < data->z_buffer[y][x])
		{
			closest_object = current_object;
			data->z_buffer[y][x] = d;
		}
		current_object = current_object->next;
	}
	if (closest_object)
	{
		d = get_intersection_distance(closest_object, ray, -1);
		intersection = add(ray->origin, mul(ray->direction, d));
		color = get_pixel_lighting(data, closest_object, intersection);
		ft_mlx_pixel_put(data->img, x, y, rgb_to_int(color));
	}
}
```

```css
int	raytracing(t_data *data)
{
	t_ray	ray;
	int		x;
	int		y;

	y = 0;
	get_camera_axis_and_viewing_plane(data);
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			data->z_buffer[y][x] = DBL_MAX;
			ray.direction = get_ray_direction(data, x, y);
			ray.origin = data->camera.pos;
			render(data, &ray, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
```

```css
double	get_intersection_distance(t_object *object, t_ray *ray, int code)
{
	double	d;

	d = -1;
	if (object->type == SPHERE)
		d = sphere_intersection(&object->u_specific.sphere,
				ray, object, code);
	else if (object->type == CYLINDER)
	{
		d = cylinder_intersection(&object->u_specific.cylinder,
				ray, object, code);
		object->u_specific.cylinder.disk = 0;
	}
	else if (object->type == PLANE)
		d = plane_intersection(&object->u_specific.plane,
				ray, &object->pos);
	else if (object->type == CONE)
		d = cone_intersection(&object->u_specific.cone, ray,
				object, code);
	return (d);
}
```

### Lighting![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Lighting">

```css
t_color	get_pixel_lighting(t_data *data, t_object *object,
		t_vector intersection)
{
	t_shadow	parts;
	t_light		*current_light;

	if (object->checkerboard)
		object->color = apply_checkerboard_pattern(object, intersection);
	init_lighting(&parts, data, object, intersection);
	current_light = data->light;
	while (current_light)
	{
		parts.light_dir = sub(current_light->pos, intersection);
		normalize_vector(&parts.light_dir);
		parts.normal = get_object_normal(intersection, object);
		parts.d_light = get_light_distance(current_light->pos, intersection);
		parts.shadow_factor = get_shadow_factor(data, intersection,
				current_light);
		parts.diffuse = get_diffuse_lighting(current_light, &parts,
				object->color);
		parts.specular = get_specular_lighting(current_light, &parts,
				parts.view_dir, parts.shininess);
		add_color(&parts);
		current_light = current_light->next;
	}
	return (parts.color);
}
```

```css
int	get_shadow_factor(t_data *data, t_vector intersection, t_light *light)
{
	t_ray		shadow_ray;
	t_object	*current_object;
	double		d;
	double		d_light;
	double		shadow_factor;

	shadow_factor = -1.0;
	shadow_ray.direction = sub(light->pos, intersection);
	normalize_vector(&shadow_ray.direction);
	shadow_ray.origin = add(intersection, mul(shadow_ray.direction, EPSILON));
	d_light = get_light_distance(light->pos, shadow_ray.origin);
	current_object = data->objects;
	while (current_object)
	{
		d = get_intersection_distance(current_object, &shadow_ray, 1);
		if (d > EPSILON && d < d_light - EPSILON)
		{
			if (shadow_factor < 0 || d < shadow_factor)
				shadow_factor = d;
		}
		current_object = current_object->next;
	}
	return (shadow_factor);
}
```

### Perlin algorithm![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Perlin algorithm">

```css
void	perturb_normal(t_vector *normal, t_object *object,
		t_vector intersection)
{
	double	theta;
	double	height;
	double	noise_value;

	theta = define_theta(object, normal, intersection);
	height = define_height(object, normal, intersection);
	noise_value = get_noise_value(object, theta, height);
	normal->x += noise_value * object->noise.intensity;
	normal->y += noise_value * object->noise.intensity;
	normal->z += noise_value * object->noise.intensity;
}
```

```css
double	perlin(double x, double y)
{
	t_perlin	parts;

	if (x >= 0)
		parts.int_x = (int)x;
	else
		parts.int_x = (int)x - 1;
	if (y >= 0)
		parts.int_y = (int)y;
	else
		parts.int_y = (int)y - 1;
	parts.frac_x = x - parts.int_x;
	parts.frac_y = y - parts.int_y;
	parts.a = generate_smooth_noise(parts.int_x, parts.int_y);
	parts.b = generate_smooth_noise(parts.int_x + 1, parts.int_y);
	parts.c = generate_smooth_noise(parts.int_x, parts.int_y + 1);
	parts.d = generate_smooth_noise(parts.int_x + 1, parts.int_y + 1);
	parts.interpolate_x1 = linear_interpolation(parts.a, parts.b,
			parts.frac_x);
	parts.interpolate_x2 = linear_interpolation(parts.c, parts.d,
			parts.frac_x);
	return (linear_interpolation(parts.interpolate_x1, parts.interpolate_x2,
			parts.frac_y));
}
```

### Checkerboard algorithm![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Checkerboard algorithm">

```css
t_color	apply_checkerboard_pattern(t_object *object, t_vector inter)
{
	t_checker	checker;

	init_checker(&checker);
	if (object->type == PLANE)
	{
		if (fabs(object->u_specific.plane.normal.y)
			> fabs(object->u_specific.plane.normal.x))
			return (apply_smooth_checkerboard_to_plane(inter, &checker));
		else
			return (apply_checkerboard_to_vertical_plane(inter, &checker));
	}
	else if (object->type == SPHERE)
		return (apply_checkerboard_to_sphere(object, inter, &checker));
	else if (object->type == CYLINDER)
		return (apply_checkerboard_to_cylinder(object, inter, &checker));
	else if (object->type == CONE)
		return (apply_checkerboard_to_cone(object, inter, &checker));
	return (object->color);
}
```

### Conclusion![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Conclusion">

### Thanks![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Thanks">
