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

### Render![---------------------------------------------------](https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/rainbow.png)

<section id="Render">

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
