<div align="left">

### 42_cursus_miniRT![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<div align="left">
    
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

<nav>
    
### Summary![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

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

The fourth circle of projects at 42 school offers students two choices in the field of graphics: Cub3d, a minimalist 3D game based on raycasting, and MiniRT, which involves developing a raytracing engine capable of generating images following the principles of geometric optics. Cub3d, with its focus on creating an interactive 2.5D environment, is often favored for its fun aspect. MiniRT, however, is perceived as a more technical project, requiring a deep understanding of algorithms and mathematics applied to image synthesis. It was this algorithmic and mathematical aspect that piqued my interest, despite my initially literary background. I wanted to tackle a project that would require me to deepen these skills while taking on a personal challenge.

To effectively organize the work, we divided the responsibilities with my partner. He handled the parsing of scene files and the integration of the graphics library, while I took charge of implementing the raytracing and associated algorithms.

In my view, MiniRT is based on two essential pillars: on the one hand, the implementation of complex algorithms in C language, such as the Perlin algorithm for procedural noise; on the other hand, the progressive learning of the steps involved in raytracing, from ray intersections with objects to managing reflections and shadows. This README aims to retrace these various stages, highlighting the challenges encountered and the solutions provided.

<div align="left">

### Render![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Render">

<div align="left">
	
#### temple.rt

<div align="center">

  <a href="https://github.com/FlorentBelotti/42_cursus_miniRT">
<img src="https://github.com/FlorentBelotti/42_cursus_miniRT/blob/main/Scene/render/Capture%20d%E2%80%99%C3%A9cran%20du%202024-09-16%2022-32-38.png" alt="GIF Description" width="80%">

  </a>&nbsp;&nbsp;&nbsp;&nbsp;

<div align="left">

#### eclipse.rt

<div align="center">

  <a href="https://github.com/FlorentBelotti/42_cursus_miniRT">
<img src="https://github.com/FlorentBelotti/42_cursus_miniRT/blob/main/Scene/render/Capture%20d%E2%80%99%C3%A9cran%20du%202024-09-16%2022-35-00.png" alt="GIF Description" width="80%">
</a>&nbsp;&nbsp;&nbsp;&nbsp;

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



#### Raytracing
<section id="Raytracing">

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

The raytracing is a 3D rendering technique that simulates the path of light rays through a virtual scene to produce photorealistic images. It calculates how rays interact with objects in the scene, considering effects like reflection, refraction, and shadows. Each pixel of the image is determined by projecting a ray from the camera through a projection plane (the screen) and calculating interactions with objects to define the visible color from that viewpoint.

Explanation of the raytracing Function

This C function is the core of the raytracing process in the MiniRT project. It works as follows:

1. Initialization: The function initializes a ray for each pixel of the screen. Each pixel corresponds to a point from which a ray is projected from the camera through the viewing plane.
2. Loop through each pixel: Two nested while loops iterate through all the pixels of the window, defined by WINDOW_HEIGHT and WINDOW_WIDTH. Each pixel receives a unique ray whose direction is calculated based on the camera position and the viewing plane.
3. Ray calculation: For each pixel, the ray's direction is obtained with `get_ray_direction`, and the ray's origin is set to the camera's position (`data->camera.pos`).
4. Object rendering: The `render` function takes the ray and tests its interactions with the scene's objects, determining the final pixel color based on the objects encountered (whether they reflect, refract, or absorb light).

The Z-buffer (stored in `data->z_buffer`) is initialized to a maximum value (`DBL_MAX`) for each pixel. It is used to store the distance to the nearest visible object to avoid overlapping issues.


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

The `render` function is responsible for the final rendering. It processes, pixel by pixel, the ray cast by the `raytracing` function and determines both the coordinates of the intersection with one of the predefined objects in the scene (described in the `scene.rt` file) and the pixel's color based on its lighting and shadows cast by other objects in the scene. In summary, it breaks down into two main steps:

1. Determine the closest intersection: In the first loop, it identifies the closest intersection to the ray's origin (i.e., the camera's position).
2. Process the intersection: If an intersection is found, it calculates the exact position of the intersection point in space (based on the distance traveled by the ray and its direction). Then, it determines the pixel's color by considering the lighting and specific characteristics defined in the `scene.rt` file, such as shading or reflection effects.

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

The `get_intersection_distance` function is designed to define the equation to be solved to determine if there is an intersection with one of the objects specified by the subject. It allows obtaining two different distances depending on the code passed as a parameter. If the code is `-1`, the function returns the distance corresponding to the closest intersection from the ray's origin. If the code is `1`, it returns the distance of the farthest intersection. However, this does not necessarily mean that it returns the intersection with the object's other face.

In reality, this distinction helps to determine whether we want to obtain the entry intersection (where the ray first meets the object, the pixel directly visible from the camera) or the exit intersection (the point where the ray leaves the object, corresponding to its opposite face). This distinction is crucial for managing both object rendering, which requires the entry intersection, and shadow processing, which often uses the exit intersection.

We will not go into the details of the intersection equations here. However, in most cases (except for the plane), it involves solving the object's quadratic equation in C. The plane and the cylinder differ slightly from other shapes. The plane does not require solving a quadratic equation, while the cylinder requires considering both the intersection with the cylinder's body and managing intersections with the disks (or "caps" in the code) at its ends.

#### Lighting
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
The `get_pixel_lighting` function applies raytracing principles at the scale of a single pixel. It sends a light ray from the object's intersection point to the light source. For each light source defined in the `scene.rt` file, the direction of this ray is calculated. Then, the function determines each light source's contribution as follows:

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

1. Ambient light: It is uniform throughout the scene, so its influence is constant and equal on each pixel.
   
3. Shadow factor: This factor measures the intensity of the shadow applied to the pixel. The higher the factor, the more pronounced the shadow. To calculate this value, a "shadow ray" is sent from the intersection point to the light source, allowing us to assess if the pixel is partially or fully in shadow.

4. Diffuse light: It is the direct light cast by a light source on the object. It depends on the angle between the light ray's direction and the object's surface.

5. Specular light: This component is responsible for the intense reflections near light sources. It creates a "halo" effect by saturating the most directly exposed pixels, adding depth and texture to the object.

#### Perlin algorithm
<section id="Perlin algorithm">

The Perlin algorithm is a popular technique for generating procedural textures in a realistic and organic manner, often used to create effects like rough surfaces, clouds, or geometry perturbations in 3D simulations. Unlike regular patterns, Perlin generates smooth, continuous "noise" that is well-suited for natural variations. In the context of raytracing, it can be used to add complex details to objects by slightly perturbing their surfaces, creating bump mapping effects (relief) without having to model complex geometry.


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

The `perturb_normal` function applies a bump mapping effect to an object's surface by slightly modifying the normal at the intersection point using Perlin noise. This perturbation simulates irregularities on the object's surface, giving it a more detailed and realistic appearance.

`perturb_normal` is called when the Perlin effect is enabled in the `scene.rt` file. This function is then involved in the diffuse light calculation, perturbing the normal to simulate a relief on the object's surface.

1. Inputs:
   - `normal`: The normal vector at the intersection point of the object.
   - `object`: The object to which the normal is applied.
   - `intersection`: The intersection point between the ray and the object.

2. Functionality:
   - `theta` and `height` are parameters used to determine the local position of the intersection point on the object.
   - Perlin noise is calculated based on these parameters to obtain a perturbation value (`noise_value`).
   - This value is then applied to the `x`, `y`, and `z` components of the normal, slightly modifying its direction based on the object's noise intensity (`object->noise.intensity`).

This process subtly deforms the normal, creating the illusion of an irregular surface without modifying the object's geometry.

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

The `perlin` function generates a two-dimensional Perlin noise value based on the `x` and `y` coordinates. This value is used to perturb an object's surface in a smooth and continuous manner.

1. Inputs:
   - `x` and `y`: The coordinates for which the noise will be calculated.

2. Functionality:
   - Integer and fractional parts: The `x` and `y` coordinates are separated into their integer (`int_x`, `int_y`) and fractional (`frac_x`, `frac_y`) parts, necessary for interpolation between different noise values.
   - Noise calculation: Four smooth noise values are generated at the corners of the cell defined by the integer parts of `x` and `y`. These values are obtained by the `generate_smooth_noise` function.
   - Linear interpolation: The corner noise values are interpolated first along the `x` axis, then along the `y` axis, to obtain a smooth transition between points.
   - Result: The final result is a smooth, continuous noise that varies based on the `x` and `y` coordinates, producing a realistic and organic texture.

#### Checkerboard algorithm
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

The `apply_checkerboard_pattern` function applies a checkerboard pattern to the objects in the scene. The checkerboard is a repetitive pattern of alternating colored squares (usually black and white) that gives a characteristic visual effect. The function handles several types of objects: planes, spheres, cylinders, and cones, adapting the pattern to the geometry of each object.


### Conclusion![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Conclusion">

If I have one piece of advice to give, it would be to focus on getting a basic render as quickly as possible, no matter how simple it is. This initial render will serve as a guideline for the project, making it easier to verify progress and improvements as you go.

### Thanks![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Thanks">

<p>
To <a href="https://github.com/Rrodor">Rrodor (Romeo Rodor)</a>: who provided guidance on the project's logic, and its various algorithms.
</p>
To Sherpa: who provided source on Perlin algorithm, and advices.
</p>
