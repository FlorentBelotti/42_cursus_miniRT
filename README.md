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

<div align="left">
	
#### temple.rt

<div align="center">

  <a href="https://github.com/FlorentBelotti/42_cursus_miniRT">
<img src="https://github.com/FlorentBelotti/42_cursus_miniRT/blob/main/Scene/render/Capture%20d%E2%80%99%C3%A9cran%20du%202024-09-16%2022-32-38.png" alt="Description du GIF" width="80%">

  </a>&nbsp;&nbsp;&nbsp;&nbsp;

<div align="left">

#### eclipse.rt

<div align="center">

  <a href="https://github.com/FlorentBelotti/42_cursus_miniRT">
<img src="https://github.com/FlorentBelotti/42_cursus_miniRT/blob/main/Scene/render/Capture%20d%E2%80%99%C3%A9cran%20du%202024-09-16%2022-35-00.png" alt="Description du GIF" width="80%">
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

Le raytracing est une technique de rendu 3D qui simule le chemin suivi par les rayons de lumière à travers une scène virtuelle pour produire des images photoréalistes. Il calcule la manière dont les rayons interagissent avec les objets de la scène, prenant en compte des effets tels que la réflexion, la réfraction et les ombres. Chaque pixel de l'image est déterminé en projetant un rayon depuis la caméra à travers un plan de projection (l'écran), et en calculant les interactions avec les objets pour définir la couleur visible depuis ce point de vue.
Explication de la Fonction raytracing

Cette fonction en C constitue le cœur du processus de raytracing dans le projet MiniRT. Elle fonctionne comme suit :

1. Initialisation : La fonction initialise un rayon pour chaque pixel de l'écran. Chaque pixel correspond à un point d'où un rayon est projeté depuis la caméra à travers le plan de visualisation.
2. Boucle sur chaque pixel : Deux boucles while imbriquées permettent de parcourir tous les pixels de la fenêtre, définis par WINDOW_HEIGHT et WINDOW_WIDTH. Chaque pixel reçoit un rayon unique dont la direction est calculée en fonction de la position de la caméra et du plan de visualisation.
3. Calcul du rayon : Pour chaque pixel, la direction du rayon est obtenue avec get_ray_direction, et l'origine du rayon est définie à la position de la caméra (data->camera.pos).
4. Rendu des objets : La fonction render prend le rayon et teste ses interactions avec les objets de la scène, déterminant ainsi la couleur finale du pixel en fonction des objets rencontrés (s'ils réfléchissent, réfractent ou absorbent la lumière).

Le Z-buffer (stocké dans data->z_buffer) est initialisé à une valeur maximale (DBL_MAX) pour chaque pixel. Il est utilisé pour stocker la distance au premier objet visible pour éviter les problèmes de superposition.


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

La fonction render est responsable du rendu final. Elle traite, pixel par pixel, le rayon lancé par la fonction raytracing et détermine, d'une part, les coordonnées de l'intersection avec l'un des objets prédéfinis dans la scène (décrite dans le fichier scene.rt), et d'autre part, la couleur du pixel en fonction de son éclairage et des ombres projetées par les autres objets de la scène. En résumé, elle se décompose en deux étapes principales :

Déterminer l'intersection la plus proche : Dans une première boucle, elle identifie l'intersection la plus proche de l'origine du rayon (c'est-à-dire la position de la caméra).

Traiter l'intersection : Si une intersection est trouvée, elle calcule la position exacte du point d'intersection dans l'espace (en fonction de la distance parcourue par le rayon et de sa direction). Ensuite, elle détermine la couleur du pixel en prenant en compte l'éclairage et les caractéristiques spécifiques définies dans le fichier scene.rt, telles que l'ombrage ou les effets de réflexion.

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

La fonction get_intersection_distance a pour but de définir l'équation à résoudre afin de déterminer s'il y a intersection avec l'un des objets spécifiés par le sujet. Elle permet d'obtenir deux distances différentes en fonction du code passé en paramètre. Si le code est -1, la fonction renvoie la distance correspondant à l'intersection la plus proche de l'origine du rayon. Si le code est 1, elle renvoie la distance de l'intersection la plus éloignée. Cependant, cela ne signifie pas qu'elle renvoie nécessairement l'intersection avec l'autre face de l'objet.

En réalité, il s'agit de distinguer si l'on souhaite obtenir l'intersection d'entrée (celle où le rayon rencontre l'objet en premier, le pixel directement visible depuis la caméra) ou l'intersection de sortie (le point où le rayon quitte l'objet, correspondant à sa face opposée). Cette distinction est cruciale pour gérer à la fois le rendu de l'objet, qui nécessite l'intersection d'entrée, et le traitement des ombres projetées, qui utilise souvent l'intersection de sortie.

Nous n'entrerons pas ici dans les détails des équations d'intersection. Cependant, dans la plupart des cas (en dehors du plan), il s'agit de résoudre en C l'équation quadratique de l'objet. Le plan et le cylindre se distinguent légèrement des autres formes. Le plan ne nécessite pas de résoudre une équation quadratique, tandis que pour le cylindre, il faut à la fois considérer l'intersection avec le corps du cylindre et gérer les intersections avec les disques (ou "caps" dans le code) situés à ses extrémités.

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

La fonction get_pixel_lighting applique les principes du raytracing à l'échelle d'un unique pixel. Elle envoie un rayon lumineux depuis le point d'intersection de l'objet jusqu'à la source de lumière. Pour chaque source de lumière définie dans le fichier scene.rt, la direction de ce rayon est calculée. Ensuite, la fonction détermine la contribution de chaque source de lumière de la manière suivante :

1. Lumière ambiante : Elle est uniforme à travers toute la scène, son influence est donc constante et égale sur chaque pixel.

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

2. Facteur d'ombre : Ce facteur mesure l'intensité de l'ombre appliquée au pixel. Plus ce facteur est élevé, plus l'ombre sera prononcée. Pour calculer cette valeur, un "rayon d'ombre" est envoyé depuis l'intersection jusqu'à la source de lumière, permettant d'évaluer si le pixel est partiellement ou entièrement dans l'ombre.

3. Lumière diffuse : Il s'agit de la lumière directe projetée par une source lumineuse sur l'objet. Elle dépend de l'angle entre la direction du rayon lumineux et la surface de l'objet.
4. Lumière spéculaire : Cette composante est responsable des reflets intenses proches des sources lumineuses. Elle crée un effet de "halo" en saturant les pixels les plus directement exposés, ajoutant ainsi du relief et de la matière à l'objet.

#### Perlin algorithm
<section id="Perlin algorithm">

L'algorithme de Perlin est une technique populaire pour générer des textures procédurales de manière réaliste et organique, souvent utilisée pour créer des effets comme des surfaces rugueuses, des nuages, ou des perturbations de la géométrie dans des simulations 3D. Contrairement aux motifs réguliers, Perlin génère un "bruit" doux et continu qui se prête bien aux variations naturelles. Dans le cadre du raytracing, il peut être utilisé pour ajouter des détails complexes aux objets en perturbant légèrement leurs surfaces, créant des effets de bump mapping (relief) sans avoir à modéliser une géométrie complexe.

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

La fonction perturb_normal applique un effet de bump mapping sur la surface d'un objet en modifiant légèrement la normale au point d'intersection grâce au bruit de Perlin. Cette perturbation simule des irrégularités sur la surface de l'objet, lui donnant un aspect plus détaillé et réaliste.

On appelle perturb_normal lorsque l'effet de Perlin est activé dans le fichier scene.rt. Cette fonction intervient alors dans le calcul de la lumière diffuse, en perturbant la normale de manière à simuler un relief sur la surface de l'objet.

1. Entrées :
- normal : Le vecteur normal au point d'intersection de l'objet.
- object : L'objet auquel la normale est appliquée.
- intersection : Le point d'intersection entre le rayon et l'objet.

2. Fonctionnement :
- theta et height sont des paramètres utilisés pour déterminer la position locale du point d'intersection sur l'objet.
- Le bruit de Perlin est calculé en fonction de ces paramètres pour obtenir une valeur de perturbation (noise_value).
- Cette valeur est ensuite appliquée aux composantes x, y et z de la normale, modifiant ainsi légèrement sa direction en fonction de l'intensité du bruit de l'objet (object->noise.intensity).

Ce processus déforme subtilement la normale, ce qui donne l'illusion d'une surface irrégulière sans modifier la géométrie de l'objet.

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

La fonction perlin génère une valeur de bruit de Perlin bidimensionnelle en fonction des coordonnées x et y. Cette valeur est utilisée pour perturber la surface d'un objet de manière fluide et continue.

1. Entrées :
- x et y : Les coordonnées à partir desquelles le bruit sera calculé.

2. Fonctionnement :
- Partie entière et fractionnaire : Les coordonnées x et y sont séparées en leurs parties entières (int_x, int_y) et fractionnaires (frac_x, frac_y), nécessaires pour interpoler entre les différentes valeurs de bruit.
- Calcul du bruit : Quatre valeurs de bruit lissé sont générées aux coins de la cellule définie par les parties entières de x et y. Ces valeurs sont obtenues par la fonction generate_smooth_noise.
- Interpolation linéaire : Les valeurs de bruit des coins sont interpolées d'abord le long de l'axe x, puis le long de l'axe y, pour obtenir une transition fluide entre les points.
- Résultat : Le résultat final est un bruit lissé et continu qui varie en fonction des coordonnées x et y, produisant une texture réaliste et organique.

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

Cette fonction applique un motif de damier sur les objets de la scène. Le damier est un motif répétitif de carrés de couleurs alternées (généralement noir et blanc) qui donne un effet visuel caractéristique. La fonction traite plusieurs types d'objets : les plans, les sphères, les cylindres et les cônes, en adaptant le motif à la géométrie de chaque objet.

### Conclusion![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Conclusion">

### Thanks![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)
<section id="Thanks">

<p>
To <a href="https://github.com/Rrodor">Rrodor (Romeo Rodor)</a>: who provided guidance on the project's logic, and its various algorithms.
</p>
