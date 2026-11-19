#ifndef PACGFX_GEOMETRY_VEC2_H
#define PACGFX_GEOMETRY_VEC2_H

typedef struct {
    double x;
    double y;
} vec2;

/* Arithmetic */
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_negate(vec2 a);
vec2 vec2_scale(vec2 a, double scalar);
/* Precondition: scalar != 0. No silent clamping. */
vec2 vec2_divide(vec2 a, double scalar);

/* Geometric properties */
double vec2_length(vec2 a);
double vec2_length_squared(vec2 a);
double vec2_distance(vec2 a, vec2 b);
double vec2_dot(vec2 a, vec2 b);
/* z-component of the 3D cross product. */
double vec2_cross(vec2 a, vec2 b);

/* Vector operations */
/* Returns the zero vector if a has (approximately) zero length. */
vec2 vec2_normalize(vec2 a);
/* a rotated 90 degrees counter-clockwise. */
vec2 vec2_perpendicular(vec2 a);
/* Unsigned angle in [0, pi]. Returns 0 if either vector is (approximately) zero. */
double vec2_angle(vec2 a, vec2 b);

/* Interpolation and comparison */
vec2 vec2_lerp(vec2 a, vec2 b, double t);
int vec2_equal(vec2 a, vec2 b);

#endif

