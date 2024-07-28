<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <header>
        <h1>42_cursus_miniRT</h1>
    </header>
    <h1>TO DO JB</h2>
    <ul>
        <li>Need to test key event</li>
        <li>Make sure only one object can be selected at a time</li>
        <li>Free in case of exit in the main function</li>
        <li>Ensure the code is compliant with the norm</li>
        <li>Setup CMake for automating map testing</li>
    </ul>
    <pre>
    lllklll
    int ft_strcmp(char *s1, char *s2)
    {
        while (*s1 && (*s1 == *s2))
        {
            s1++;
            s2++;
        }
        return (*(unsigned char *)s1 - *(unsigned char *)s2);
    }
    </pre>
    <h1>Ray-Sphere Intersection in 3D</h1>
    <p>This document explains how to determine the intersection of a ray with a sphere in 3D space, using both mathematical concepts and code implementation.</p>
    <h2>1. Sphere Equation in 3D</h2>
    <p>A sphere in 3D space is defined by the equation:</p>
    <pre>(x - x_center)^2 + (y - y_center)^2 + (z - z_center)^2 = r^2</pre>
    <p>Where <code>(x_center, y_center, z_center)</code> is the center of the sphere and <code>r</code> is its radius.</p>
    <h2>2. Ray Parameterization</h2>
    <p>A ray in 3D space can be represented as:</p>
    <pre>(x, y, z) = Origin + t * Direction</pre>
    <p>Where <code>Origin = (Ox, Oy, Oz)</code> is the starting point of the ray, <code>Direction = (Dx, Dy, Dz)</code> is the direction vector, and <code>t</code> is a scalar that determines points along the ray.</p>
    <h2>3. Substitution and Expansion</h2>
    <p>To find the intersection points, substitute the ray's coordinates into the sphere's equation:</p>
    <pre>((Dx * t + Ox) - x_center)^2 + ((Dy * t + Oy) - y_center)^2 + ((Dz * t + Oz) - z_center)^2 = r^2</pre>
    <h2>4. Quadratic Equation</h2>
    <p>Expanding the equation results in a quadratic equation in <code>t</code>:</p>
    <pre>A * t^2 + B * t + C = 0</pre>
    <p>Where:</p>
    <ul>
        <li><code>A = Dx^2 + Dy^2 + Dz^2</code></li>
        <li><code>B = 2 * (Dx * (Ox - x_center) + Dy * (Oy - y_center) + Dz * (Oz - z_center))</code></li>
        <li><code>C = (Ox - x_center)^2 + (Oy - y_center)^2 + (Oz - z_center)^2 - r^2</code></li>
    </ul>
    <h2>5. Discriminant</h2>
    <p>The discriminant, <code>Δ</code>, determines the nature of the intersection:</p>
    <pre>Δ = B^2 - 4 * A * C</pre>
    <p>Where:</p>
    <ul>
        <li><strong>Δ &gt; 0</strong>: Two intersection points (the ray enters and exits the sphere).</li>
        <li><strong>Δ = 0</strong>: One intersection point (the ray tangents the sphere).</li>
        <li><strong>Δ &lt; 0</strong>: No intersection.</li>
    </ul>
    <h2>6. Calculating Intersection Points</h2>
    <p>If <code>Δ ≥ 0</code>, the intersections are calculated as:</p>
    <pre>t1 = (-B - sqrt(Δ)) / (2 * A)</pre>
    <pre>t2 = (-B + sqrt(Δ)) / (2 * A)</pre>
    <p>These values represent the distances along the ray to the intersection points.</p>
</body>
</html>
