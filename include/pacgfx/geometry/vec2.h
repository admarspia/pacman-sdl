#ifndef VEC2_H
#define VEC2_H
#include "./approx.h"

typedef struct {
  double x;
  double y;
}vec2;


// Arithmetic
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_negate(vec2 a);
vec2 vec2_scale(vec2 a, double scalar);
vec2 vec2_divide(vec2 a, double scalar);

// Geometric properties
double vec2_length(vec2 a);
double vec2_length_squared(vec2 a);
double vec2_distance(vec2 a, vec2 b);
double vec2_dot(vec2 a, vec2 b);
double vec2_cross(vec2 a, vec2 b);

// Vector operations
vec2 vec2_normalize(vec2 a);
vec2 vec2_perpendicular(vec2 a);
double vec2_angle(vec2 a, vec2 b);

// Interpolation and comparison
vec2 vec2_lerp(vec2 a, vec2 b, double t);
int vec2_equal(vec2 a, vec2 b);


#endif


