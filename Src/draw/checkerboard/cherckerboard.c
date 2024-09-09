#include "miniRT.h"

#define CHECKERBOARD_SCALE 5.0
#define CHECKERBOARD_EPSILON 1e-6
#define M_PI 3.14159265358979323846

t_color smooth_checkerboard(t_color color1, t_color color2, double factor)
{
    t_color result;

    result.r = (int)((1 - factor) * color1.r + factor * color2.r);
    result.g = (int)((1 - factor) * color1.g + factor * color2.g);
    result.b = (int)((1 - factor) * color1.b + factor * color2.b);

    return result;
}

t_color apply_smooth_checkerboard_to_plane(t_object *object, t_vector intersection)
{
    double scale = 5.0;  // Adjust scale for the size of the checkerboard pattern
    double x = intersection.x / scale;
    double z = intersection.z / scale;

    // Calculate whether the point is inside a square (0 or 1 for a basic checkerboard pattern)
    int check_x = (int)floor(x) % 2;
    int check_z = (int)floor(z) % 2;
    int is_black_square = (check_x + check_z) % 2;

    // Calculate the distances to the nearest grid lines for smoothing
    double dist_x = fabs(x - round(x));
    double dist_z = fabs(z - round(z));

    // Smooth the edge based on the distance to the nearest grid lines
    double smooth_factor = fmax(dist_x, dist_z);
    smooth_factor = smooth_factor * smooth_factor * (3 - 2 * smooth_factor); // Smootherstep function

    // Determine the base colors (black or object color)
    t_color color1 = is_black_square ? (t_color){0, 0, 0} : object->color;
    t_color color2 = is_black_square ? object->color : (t_color){0, 0, 0};

    // Blend between the colors based on the smooth factor
    return smooth_checkerboard(color1, color2, smooth_factor);
}

// Apply checkerboard pattern for vertical planes (walls)
t_color apply_checkerboard_to_vertical_plane(t_object *object, t_vector intersection)
{
    double scale = 5.0;  // Adjust scale for the size of the checkerboard pattern
    double y = intersection.y;
    double z = intersection.z;

    // Vertical Plane: Use y and z coordinates
    int pattern = (int)(floor(y / scale) + floor(z / scale)) % 2;

    // Return either black or the object's original color based on the pattern
    return (pattern == 0) ? (t_color){0, 0, 0} : object->color;
}


t_color apply_checkerboard_to_sphere(t_object *object, t_vector intersection)
{
    t_vector local_point = sub(intersection, object->pos);
	normalize_vector(&local_point);
    double theta = atan2(local_point.y, local_point.x);
    double phi = acos(local_point.z / (object->specific.sphere.diameter / 2.0));

    if (theta < 0) theta += 2 * M_PI;

    double u = theta / (2 * M_PI);
    double v = phi / M_PI;

    int scale_u = 10;  // You can adjust this value
    int scale_v = 10;  // You can adjust this value
    int pattern = (int)(floor(u * scale_u) + floor(v * scale_v)) % 2;

	//EPSILON LE FRATE sphere_intersection
    return (pattern == 0) ? (t_color){0, 0, 0} : object->color;
}

// Apply checkerboard pattern to Cylinder
t_color apply_checkerboard_to_cylinder(t_object *object, t_vector intersection)
{
    t_vector local_point = sub(intersection, object->pos);
	normalize_vector(&local_point);
    double theta = atan2(local_point.y, local_point.x);
    double v = local_point.z / object->specific.cylinder.height;

    // Adjust theta to avoid issues at the seam
    if (theta < 0) theta += 2 * M_PI;

    double u = theta / (2 * M_PI);
    int scale_u = 5;  // Adjust for smaller squares
    int scale_v = 10;  // Adjust for smaller squares
    int pattern = (int)(floor(u * scale_u) + floor(v * scale_v)) % 2;

    return (pattern == 0) ? (t_color){0, 0, 0} : object->color;
}


// Main checkerboard application function that selects the correct method based on the object type
t_color apply_checkerboard_pattern(t_object *object, t_vector intersection)
{
    // Select the appropriate checkerboard pattern based on the object type
    if (object->type == PLANE)
    {
        // Determine if the plane is horizontal or vertical
        if (fabs(object->specific.plane.normal.y) > fabs(object->specific.plane.normal.x))
        {
            // Treat as a horizontal plane (floor or ceiling)
            return apply_smooth_checkerboard_to_plane(object, intersection);
        }
        else
        {
            // Treat as a vertical plane (walls)
            return apply_checkerboard_to_vertical_plane(object, intersection);
        }
    }
    else if (object->type == SPHERE)
    {
        return apply_checkerboard_to_sphere(object, intersection);
    }
	

    // Default return if object type is not recognized
    return object->color;
}
