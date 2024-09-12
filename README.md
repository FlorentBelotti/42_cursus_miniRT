<div align="left">

### 42_cursus_miniRT![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<div align="left">

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

Pour commencer, voici quelques exemples du rendu final de mon miniRT au moment du rendu.

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

### Lighting![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Lighting">

### Perlin algorithm![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Perlin algorithm">

### Checkerboard algorithm![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Checkerboard algorithm">

### Conclusion![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Conclusion">

### Thanks![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Thanks">
